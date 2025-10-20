import tkinter as tk
from tkinter import filedialog, messagebox, ttk
from PIL import Image, ImageTk
import os
import json # <-- Import json

class MapsTab:
    def __init__(self, notebook, editor):
        self.editor = editor
        self.data = editor.get_json_data() # Main headers data (no longer used for maps)
        
        # --- MODIFICATIONS: Map data is now self-contained ---
        self.maps_data = {} # Holds all loaded map data
        self.maps_dir = "./maps" # Directory for map files
        # ----------------------------------------------------
        
        # Create the tab frame
        self.frame = tk.Frame(notebook)
        notebook.add(self.frame, text="Maps")
        
        # Map editor state
        self.current_map_id = None
        self.current_layer = 'decor'
        self.current_tool = 'place'
        self.selected_tile = 0
        self.selected_number = 0
        self.tile_size = 32
        self.grid_size = 32
        self.zoom = 1.0
        self.tileset_image = None
        self.tileset_tiles = []
        self.tileset_path = None
        self.selection_start = None
        self.selection_rect = None

        self.selection_start = None
        self.selection_rect = None
        
        # --- Store map drawing offset ---
        self.min_x = 0
        self.min_y = 0
        # --------------------------------
        
        # --- New state variables ---
        self.clipboard_data = {}  # For copy/paste
        self.current_grid_pos = (0, 0) # For paste location
        self.undo_stack = []
        self.redo_stack = []
        self.current_action = []  # Groups changes (e.g., from a drag)
        # ---------------------------

        # Layer configuration
        self.layer_order = ['metadata', 'actions', 'characters', 'decor', 'colliders']
        self.layer_types = {
            'metadata': 'number',
            'actions': 'number',
            'characters': 'number',
            'decor': 'tile',
            'colliders': 'tile'
        }
        
        self.layer_colors = {
            'metadata': '#FF6B6B',
            'actions': '#4ECDC4',
            'characters': '#45B7D1',
            'decor': '#96CEB4',
            'colliders': '#FFEAA7'
        }
        
        # --- NEW: Layer visibility state ---
        self.layer_visibility = {
            layer: tk.BooleanVar(value=True) for layer in self.layer_order
        }
        # -----------------------------------
        
        # --- MODIFICATION: Load maps from files on init ---
        self.load_all_maps_from_files()
        # ------------------------------------------------
        
        self.setup_ui()
        self.bind_shortcuts()
        
    def setup_ui(self):
        # Top toolbar for map selection
        toolbar = tk.Frame(self.frame, bg='#34495E', height=50)
        toolbar.pack(side=tk.TOP, fill=tk.X, padx=5, pady=5)
        toolbar.pack_propagate(False)
        
        tk.Label(toolbar, text="Map:", bg='#34495E', fg='white', font=('Arial', 10, 'bold')).pack(side=tk.LEFT, padx=5)
        
        self.map_var = tk.StringVar()
        self.map_dropdown = ttk.Combobox(toolbar, textvariable=self.map_var, state='readonly', width=20)
        self.map_dropdown.pack(side=tk.LEFT, padx=5)
        self.map_dropdown.bind('<<ComboboxSelected>>', self.on_map_selected)
        
        tk.Button(toolbar, text="New Map", command=self.new_map, bg='#27AE60', fg='white').pack(side=tk.LEFT, padx=5)
        tk.Button(toolbar, text="Rename Map", command=self.rename_map, bg='#3498DB', fg='white').pack(side=tk.LEFT, padx=5)
        tk.Button(toolbar, text="Delete Map", command=self.delete_map, bg='#E74C3C', fg='white').pack(side=tk.LEFT, padx=5)
        
        # --- ADDED RESIZE BUTTON ---
        tk.Button(toolbar, text="Resize Map", command=self.resize_map, bg='#F39C12', fg='white').pack(side=tk.LEFT, padx=5)
        # ---------------------------
        
        tk.Button(toolbar, text="Load Tileset", command=self.load_tileset, bg='#9B59B6', fg='white').pack(side=tk.LEFT, padx=5)
        
        # Main container
        main_frame = tk.Frame(self.frame)
        main_frame.pack(fill=tk.BOTH, expand=True)
        
        # Left panel - Tools and Layers
        left_panel = tk.Frame(main_frame, width=200, bg='#2C3E50')
        left_panel.pack(side=tk.LEFT, fill=tk.Y, padx=5, pady=5)
        left_panel.pack_propagate(False)
        
        # Tools section
        tools_label = tk.Label(left_panel, text="Tools", bg='#2C3E50', fg='white', font=('Arial', 12, 'bold'))
        tools_label.pack(pady=5)
        
        self.tool_var = tk.StringVar(value='place')
        tools = [('Place (P)', 'place'), ('Erase (E)', 'erase'), ('Select (S)', 'select')]
        for text, tool in tools:
            rb = tk.Radiobutton(left_panel, text=text, variable=self.tool_var, value=tool,
                                command=lambda t=tool: self.set_tool(t),
                                bg='#34495E', fg='white', selectcolor='#2C3E50',
                                activebackground='#34495E', activeforeground='white')
            rb.pack(anchor=tk.W, padx=10, pady=2)
        
        # Layers section
        tk.Label(left_panel, text="Layers", bg='#2C3E50', fg='white', font=('Arial', 12, 'bold')).pack(pady=(20, 5))
        
        self.layer_var = tk.StringVar(value='decor')
        
        # --- MODIFIED: Add Checkboxes for visibility ---
        for layer in reversed(self.layer_order):
            
            # Create a frame to hold both the checkbox and radio button
            layer_frame = tk.Frame(left_panel, bg='#34495E')
            layer_frame.pack(anchor=tk.W, fill=tk.X, padx=10, pady=0)
            
            # 1. Visibility Checkbox
            cb = tk.Checkbutton(layer_frame, variable=self.layer_visibility[layer],
                                command=self.draw_canvas, # Redraw when toggled
                                bg='#34495E', selectcolor='#2C3E50',
                                activebackground='#34495E',
                                relief=tk.FLAT, borderwidth=0, highlightthickness=0)
            cb.pack(side=tk.LEFT, pady=0)

            # 2. Layer Selection Radiobutton
            layer_type = self.layer_types[layer]
            text = f"{layer} ({layer_type})"
            rb = tk.Radiobutton(layer_frame, text=text, variable=self.layer_var, value=layer,
                                command=lambda l=layer: self.set_layer(l),
                                bg='#34495E', fg='white', selectcolor='#2C3E50',
                                activebackground='#34495E', activeforeground='white',
                                justify=tk.LEFT, anchor=tk.W,
                                indicatoron=True) # Keep the radio dot
            rb.pack(side=tk.LEFT, fill=tk.X, expand=True, pady=0)
        # -----------------------------------------------
        
        # Info label
        self.info_label = tk.Label(left_panel, text="Right-click to erase", bg='#2C3E50', 
                                   fg='#95A5A6', font=('Arial', 9, 'italic'))
        self.info_label.pack(pady=(20, 5))
        
        # Zoom controls
        tk.Label(left_panel, text="Zoom:", bg='#2C3E50', fg='white').pack(pady=(20, 5))
        zoom_frame = tk.Frame(left_panel, bg='#2C3E50')
        zoom_frame.pack()
        tk.Button(zoom_frame, text="-", command=self.zoom_out, width=3).pack(side=tk.LEFT, padx=2)
        tk.Button(zoom_frame, text="+", command=self.zoom_in, width=3).pack(side=tk.LEFT, padx=2)
        
        # Center panel - Canvas
        canvas_frame = tk.Frame(main_frame)
        canvas_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        # Canvas with scrollbars
        self.canvas = tk.Canvas(canvas_frame, bg='#1a1a1a', highlightthickness=0)
        h_scroll = tk.Scrollbar(canvas_frame, orient=tk.HORIZONTAL, command=self.canvas.xview)
        v_scroll = tk.Scrollbar(canvas_frame, orient=tk.VERTICAL, command=self.canvas.yview)
        self.canvas.config(xscrollcommand=h_scroll.set, yscrollcommand=v_scroll.set)
        
        h_scroll.pack(side=tk.BOTTOM, fill=tk.X)
        v_scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        # Bind canvas events --- UPDATED BINDINGS ---
        self.canvas.bind('<ButtonPress-1>', self.on_canvas_press_1)
        self.canvas.bind('<B1-Motion>', self.on_canvas_drag)
        self.canvas.bind('<ButtonRelease-1>', self.on_canvas_release_1)
        self.canvas.bind('<Motion>', self.on_canvas_motion)
        self.canvas.bind('<ButtonPress-3>', self.on_canvas_press_3)
        self.canvas.bind('<B3-Motion>', self.on_canvas_right_drag)
        self.canvas.bind('<ButtonRelease-3>', self.on_canvas_release_3)
        
        # Right panel - Tileset
        right_panel = tk.Frame(main_frame, width=250, bg='#2C3E50')
        right_panel.pack(side=tk.RIGHT, fill=tk.Y, padx=5, pady=5)
        right_panel.pack_propagate(False)
        
        self.tileset_label = tk.Label(right_panel, text="Tileset", bg='#2C3E50', fg='white', 
                                      font=('Arial', 12, 'bold'))
        self.tileset_label.pack(pady=5)
        
        # Tileset canvas with scrollbar
        tileset_container = tk.Frame(right_panel)
        tileset_container.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)
        
        self.tileset_canvas = tk.Canvas(tileset_container, bg='#34495E', highlightthickness=1,
                                        highlightbackground='white')
        tileset_scroll = tk.Scrollbar(tileset_container, orient=tk.VERTICAL, command=self.tileset_canvas.yview)
        self.tileset_canvas.config(yscrollcommand=tileset_scroll.set)
        
        tileset_scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.tileset_canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        self.tileset_canvas.bind('<Button-1>', self.on_tileset_click)
        
        # Status bar
        self.status_bar = tk.Label(self.frame, text="Select or create a map to begin", 
                                  bd=1, relief=tk.SUNKEN, anchor=tk.W)
        self.status_bar.pack(side=tk.BOTTOM, fill=tk.X)
        
        self.refresh_map_list()
        self.draw_tileset()
        self.draw_canvas()
        
    def bind_shortcuts(self):
        # Use bind_all to catch shortcuts globally
        self.frame.bind_all('<p>', lambda e: self.set_tool('place'))
        self.frame.bind_all('<e>', lambda e: self.set_tool('erase'))
        self.frame.bind_all('<s>', lambda e: self.set_tool('select'))
        
        # --- New Bindings ---
        self.frame.bind_all('<Control-z>', self.undo)
        self.frame.bind_all('<Control-Shift-Z>', self.redo)
        self.frame.bind_all('<Control-y>', self.redo) # Common redo shortcut
        self.frame.bind_all('<Control-v>', self.paste_selection)
        
        # --- ADDED THIS LINE ---
        self.frame.bind_all('<Control-x>', self.cut_selection)
        # -----------------------

    # --- NEW: Map File Load/Save ---

    def load_all_maps_from_files(self):
        """Loads all .json files from the self.maps_dir directory."""
        self.maps_data = {}
        
        if not os.path.exists(self.maps_dir):
            try:
                os.makedirs(self.maps_dir)
                print(f"Created maps directory: {self.maps_dir}")
            except Exception as e:
                messagebox.showerror("Error", f"Could not create maps directory: {e}")
                return
        
        for filename in os.listdir(self.maps_dir):
            if filename.endswith(".json"):
                map_id = os.path.splitext(filename)[0]
                filepath = os.path.join(self.maps_dir, filename)
                try:
                    with open(filepath, "r") as f:
                        self.maps_data[map_id] = json.load(f)
                except Exception as e:
                    messagebox.showerror("Load Error", f"Failed to load map '{filename}': {e}")
        
        print(f"Loaded {len(self.maps_data)} maps.")

    def save_all_maps_to_files(self):
        """Saves all maps in self.maps_data to their individual .json files."""
        if not os.path.exists(self.maps_dir):
            try:
                os.makedirs(self.maps_dir)
            except Exception as e:
                messagebox.showerror("Error", f"Could not create maps directory for saving: {e}")
                return

        for map_id, map_data in self.maps_data.items():
            filename = f"{map_id}.json"
            filepath = os.path.join(self.maps_dir, filename)
            try:
                with open(filepath, "w") as f:
                    json.dump(map_data, f, indent=4)
            except Exception as e:
                messagebox.showerror("Save Error", f"Failed to save map '{map_id}': {e}")
        
        print(f"Saved {len(self.maps_data)} maps.")

    # ---------------------------------
        

    # --- New Undo/Redo and Action Functions ---
    
    def apply_change(self, layer_name, key, new_value):
        """
        Applies a single change to the map data and records it
        for the current undo action.
        """
        map_data = self.get_current_map_data()
        if not map_data:
            return

        layer_data = map_data["layers"][layer_name]
        old_value = layer_data.get(key)
        
        # If no actual change, do nothing
        if old_value == new_value:
            return
            
        # Record the change (before and after)
        self.current_action.append((layer_name, key, old_value, new_value))
        
        # Apply the change
        if new_value is None:
            if key in layer_data:
                del layer_data[key]
        else:
            layer_data[key] = new_value

    # --- NEW: Handle top-level property changes (width, height) ---
    def apply_property_change(self, key, new_value):
        """
        Applies a change to a top-level map property (like 'width' or 'height')
        and records it for undo.
        """
        map_data = self.get_current_map_data()
        if not map_data:
            return
        
        old_value = map_data.get(key)
        
        if old_value == new_value:
            return
            
        # Use a special layer_name 'TOP_LEVEL' to signify this
        self.current_action.append(('TOP_LEVEL', key, old_value, new_value))
        
        map_data[key] = new_value
    # -------------------------------------------------------------

    def commit_action(self):
        """Commits the grouped changes in self.current_action to the undo stack."""
        if self.current_action:
            self.undo_stack.append(self.current_action)
            self.current_action = []
            # Any new action clears the redo stack
            self.redo_stack = []
            # print(f"Action committed. Undo stack size: {len(self.undo_stack)}")

    def undo(self, event=None):
        """Performs an undo operation."""
        if not self.undo_stack:
            # print("Undo stack empty")
            return

        action_to_undo = self.undo_stack.pop()
        redo_action = [] # This will store the "forward" action for the redo stack
        
        map_data = self.get_current_map_data()
        if not map_data:
            return

        # Apply all changes in reverse order
        for layer_name, key, old_value, new_value in reversed(action_to_undo):
            
            # --- MODIFIED: Handle TOP_LEVEL property changes ---
            if layer_name == 'TOP_LEVEL':
                if old_value is None:
                    if key in map_data:
                        del map_data[key]
                else:
                    map_data[key] = old_value
            else:
            # ---------------------------------------------------
                layer_data = map_data["layers"][layer_name]
                
                # Apply the "old" value to undo
                if old_value is None:
                    if key in layer_data:
                        del layer_data[key]
                else:
                    layer_data[key] = old_value
            
            # Store the "new" value for the redo stack
            redo_action.append((layer_name, key, old_value, new_value))

        self.redo_stack.append(list(reversed(redo_action))) # Store in forward order
        self.draw_canvas()
        # print(f"Undo complete. Redo stack size: {len(self.redo_stack)}")

    def redo(self, event=None):
        """Performs a redo operation."""
        if not self.redo_stack:
            # print("Redo stack empty")
            return
            
        action_to_redo = self.redo_stack.pop()
        undo_action = [] # This will store the "reverse" action for the undo stack

        map_data = self.get_current_map_data()
        if not map_data:
            return

        # Apply all changes in forward order
        for layer_name, key, old_value, new_value in action_to_redo:
            
            # --- MODIFIED: Handle TOP_LEVEL property changes ---
            if layer_name == 'TOP_LEVEL':
                if new_value is None:
                    if key in map_data:
                        del map_data[key]
                else:
                    map_data[key] = new_value
            else:
            # ---------------------------------------------------
                layer_data = map_data["layers"][layer_name]
                
                # Apply the "new" value to redo
                if new_value is None:
                    if key in layer_data:
                        del layer_data[key]
                else:
                    layer_data[key] = new_value

            # Store the "old" value for the undo stack
            undo_action.append((layer_name, key, old_value, new_value))

        self.undo_stack.append(undo_action)
        self.draw_canvas()
        # print(f"Redo complete. Undo stack size: {len(self.undo_stack)}")

    def paste_selection(self, event=None):
        """Pastes the data from the clipboard at the current mouse position."""
        if not self.clipboard_data:
            messagebox.showinfo("Paste", "Clipboard is empty. Use the Select tool (S) to copy.")
            return

        paste_x, paste_y = self.current_grid_pos
        map_data = self.get_current_map_data()
        if not map_data:
            return
            
        self.current_action = [] # Start a new action for the paste
        
        for (rel_x, rel_y, layer_name), value in self.clipboard_data.items():
            target_x = paste_x + rel_x
            target_y = paste_y + rel_y
            key = f"{target_x},{target_y}"
            
            # --- ADDED: Check if paste is within map bounds ---
            map_width = map_data.get("width", 20)
            map_height = map_data.get("height", 20)
            if 0 <= target_x < map_width and 0 <= target_y < map_height:
                self.apply_change(layer_name, key, value)
            # --------------------------------------------------
            
        self.commit_action() # Commit the entire paste as one action
        self.draw_canvas()
        # print(f"Pasted {len(self.clipboard_data)} tiles.")

    # --- NEW: Cut/Copy/Delete Helper Functions ---
    
    def _copy_selection_to_clipboard(self, min_x, max_x, min_y, max_y):
        """Helper to copy data from a bounded area to the clipboard."""
        self.clipboard_data = {}
        map_data = self.get_current_map_data()
        if not map_data:
            return 0
            
        for x_pos in range(min_x, max_x + 1):
            for y_pos in range(min_y, max_y + 1):
                rel_x = x_pos - min_x
                rel_y = y_pos - min_y
                key = f"{x_pos},{y_pos}"
                
                for layer_name in self.layer_order:
                    layer_data = map_data["layers"][layer_name]
                    if key in layer_data:
                        value = layer_data[key]
                        self.clipboard_data[(rel_x, rel_y, layer_name)] = value
        return len(self.clipboard_data)

    def _delete_selection_area(self, min_x, max_x, min_y, max_y):
        """
        Helper to delete data from a bounded area across all layers.
        Assumes self.current_action has already been started by the caller.
        """
        map_data = self.get_current_map_data()
        if not map_data:
            return

        for x_pos in range(min_x, max_x + 1):
            for y_pos in range(min_y, max_y + 1):
                key = f"{x_pos},{y_pos}"
                for layer_name in self.layer_order:
                    # apply_change(None) will check if the key exists
                    # and record the change (from 'value' to 'None') if it does.
                    self.apply_change(layer_name, key, None)
                    
    def cut_selection(self, event=None):
        """Performs a cut operation (copy + delete) on the current selection."""
        # Only cut if we are in select mode and a selection has been started
        if self.current_tool != 'select' or not self.selection_start:
            return

        # Find the selection bounds
        start_x, start_y = self.selection_start
        grid_x, grid_y = self.current_grid_pos # Use current mouse pos
        
        min_x = min(start_x, grid_x)
        min_y = min(start_y, grid_y)
        max_x = max(start_x, grid_x)
        max_y = max(start_y, grid_y)

        # 1. Copy to clipboard
        copied_count = self._copy_selection_to_clipboard(min_x, max_x, min_y, max_y)

        # 2. Delete from map (as a single undo-able action)
        self.current_action = []
        self._delete_selection_area(min_x, max_x, min_y, max_y)
        self.commit_action()
        
        # 3. Clean up the selection UI
        if self.selection_rect:
            self.canvas.delete(self.selection_rect)
            self.selection_rect = None
        self.selection_start = None
        
        # 4. Redraw
        self.draw_canvas()
        
        if copied_count > 0:
            messagebox.showinfo("Cut", f"Cut {copied_count} tile entries to clipboard.\nUse Ctrl+V to paste.")
        else:
            messagebox.showinfo("Cut", "Cut empty selection to clipboard.")

    # ----------------------------------------
        
    def refresh_map_list(self):
        """Update the map dropdown with available maps"""
        # --- MODIFICATION: Use self.maps_data ---
        maps = list(self.maps_data.keys())
        # ----------------------------------------
        self.map_dropdown['values'] = maps
        if maps and not self.current_map_id:
            self.map_var.set(maps[0])
            self.current_map_id = maps[0]
            self.load_current_map()
        # --- MODIFICATION: Use self.maps_data ---
        elif self.current_map_id and self.current_map_id in self.maps_data:
        # ----------------------------------------
            self.map_var.set(self.current_map_id)
    
    def new_map(self):
        """Create a new map"""
        dialog = tk.Toplevel(self.frame)
        dialog.title("New Map")
        # --- MODIFIED: Made dialog taller ---
        dialog.geometry("300x200")
        # ------------------------------------
        dialog.transient(self.frame)
        dialog.grab_set()
        
        f_id = tk.Frame(dialog); f_id.pack(pady=5)
        tk.Label(f_id, text="Map ID:", width=8, anchor=tk.E).pack(side=tk.LEFT)
        entry = tk.Entry(f_id, width=30)
        entry.pack(side=tk.LEFT, padx=5)
        entry.focus()
        
        # --- ADDED: Width and Height entries ---
        f_width = tk.Frame(dialog); f_width.pack(pady=2)
        tk.Label(f_width, text="Width:", width=8, anchor=tk.E).pack(side=tk.LEFT)
        entry_w = tk.Entry(f_width, width=10); entry_w.pack(side=tk.LEFT, padx=5)
        entry_w.insert(0, "20")

        f_height = tk.Frame(dialog); f_height.pack(pady=2)
        tk.Label(f_height, text="Height:", width=8, anchor=tk.E).pack(side=tk.LEFT)
        entry_h = tk.Entry(f_height, width=10); entry_h.pack(side=tk.LEFT, padx=5)
        entry_h.insert(0, "20")
        # ---------------------------------------
        
        def create():
            map_id = entry.get().strip()
            
            # --- MODIFIED: Validate all fields ---
            try:
                width = int(entry_w.get())
                height = int(entry_h.get())
                if width <= 0 or height <= 0:
                    raise ValueError
            except ValueError:
                messagebox.showwarning("Invalid", "Width and Height must be positive numbers")
                return
            # -------------------------------------
            
            if not map_id:
                messagebox.showwarning("Invalid", "Map ID cannot be empty")
                return
            # --- MODIFICATION: Use self.maps_data ---
            if map_id in self.maps_data:
            # ----------------------------------------
                messagebox.showwarning("Exists", "Map ID already exists")
                return
            
            # --- MODIFICATION: Use self.maps_data ---
            self.maps_data[map_id] = {
            # ----------------------------------------
                # --- ADDED: Width and Height ---
                "width": width,
                "height": height,
                # -------------------------------
                "tileset": None,
                "layers": {
                    'metadata': {},
                    'actions': {},
                    'characters': {},
                    'decor': {},
                    'colliders': {}
                }
            }
            
            self.current_map_id = map_id
            self.refresh_map_list()
            self.load_current_map()
            dialog.destroy()
        
        tk.Button(dialog, text="Create", command=create).pack(pady=10)
        entry.bind('<Return>', lambda e: create())
    
    def rename_map(self):
        """Rename the current map"""
        if not self.current_map_id:
            messagebox.showwarning("No Map", "No map selected")
            return
        
        dialog = tk.Toplevel(self.frame)
        dialog.title("Rename Map")
        dialog.geometry("300x100")
        dialog.transient(self.frame)
        dialog.grab_set()
        
        tk.Label(dialog, text="New Map ID:").pack(pady=5)
        entry = tk.Entry(dialog, width=30)
        entry.insert(0, self.current_map_id)
        entry.pack(pady=5)
        entry.focus()
        entry.select_range(0, tk.END)
        
        def rename():
            new_id = entry.get().strip()
            if not new_id:
                messagebox.showwarning("Invalid", "Map ID cannot be empty")
                return
            # --- MODIFICATION: Use self.maps_data ---
            if new_id != self.current_map_id and new_id in self.maps_data:
            # ----------------------------------------
                messagebox.showwarning("Exists", "Map ID already exists")
                return
            
            if new_id != self.current_map_id:
                # --- MODIFICATION: Use self.maps_data ---
                self.maps_data[new_id] = self.maps_data.pop(self.current_map_id)
                # ----------------------------------------

                # --- MODIFICATION: Delete old file ---
                old_filename = f"{self.current_map_id}.json"
                old_filepath = os.path.join(self.maps_dir, old_filename)
                if os.path.exists(old_filepath):
                    try:
                        os.remove(old_filepath)
                    except Exception as e:
                        messagebox.showerror("Error", f"Could not remove old map file: {e}")
                # -------------------------------------

                self.current_map_id = new_id
                self.refresh_map_list()
            
            dialog.destroy()
        
        tk.Button(dialog, text="Rename", command=rename).pack(pady=5)
        entry.bind('<Return>', lambda e: rename())
    
    # --- NEW: Resize Map Function ---
    def resize_map(self):
        """Resize the current map"""
        if not self.current_map_id:
            messagebox.showwarning("No Map", "No map selected")
            return
            
        map_data = self.get_current_map_data()
        
        dialog = tk.Toplevel(self.frame)
        dialog.title("Resize Map")
        dialog.geometry("300x180")
        dialog.transient(self.frame)
        dialog.grab_set()
        
        tk.Label(dialog, text=f"Resizing '{self.current_map_id}'", font=('Arial', 10, 'bold')).pack(pady=5)
        
        # Get current dimensions, providing defaults for old maps
        current_w = map_data.get("width", 20)
        current_h = map_data.get("height", 20)
        
        f_width = tk.Frame(dialog); f_width.pack(pady=5)
        tk.Label(f_width, text="New Width:", width=10, anchor=tk.E).pack(side=tk.LEFT)
        entry_w = tk.Entry(f_width, width=10); entry_w.pack(side=tk.LEFT, padx=5)
        entry_w.insert(0, str(current_w))
        entry_w.focus()

        f_height = tk.Frame(dialog); f_height.pack(pady=5)
        tk.Label(f_height, text="New Height:", width=10, anchor=tk.E).pack(side=tk.LEFT)
        entry_h = tk.Entry(f_height, width=10); entry_h.pack(side=tk.LEFT, padx=5)
        entry_h.insert(0, str(current_h))
        
        tk.Label(dialog, text="Tiles outside the new bounds (0,0 origin)\nwill be deleted.",
                 fg='#666', font=('Arial', 8, 'italic')).pack(pady=5)

        def apply_resize():
            try:
                new_w = int(entry_w.get())
                new_h = int(entry_h.get())
                if new_w <= 0 or new_h <= 0:
                    raise ValueError
            except ValueError:
                messagebox.showwarning("Invalid", "Width and Height must be positive numbers")
                return
            
            if new_w == current_w and new_h == current_h:
                dialog.destroy()
                return
                
            if not messagebox.askyesno("Confirm Resize", 
                                      "This will delete all tiles outside the new dimensions.\n"
                                      "This action can be undone (Ctrl+Z).\n\n"
                                      "Proceed with resize?"):
                return
            
            self.current_action = []
            
            # 1. Apply property changes (undo-able)
            self.apply_property_change("width", new_w)
            self.apply_property_change("height", new_h)
            
            # 2. Delete tiles outside the new bounds (undo-able)
            for layer_name in self.layer_order:
                layer_data = map_data["layers"][layer_name]
                # Must iterate over a copy of keys since we are deleting
                keys_to_check = list(layer_data.keys()) 
                
                for key in keys_to_check:
                    try:
                        x, y = map(int, key.split(','))
                        # Check if outside new bounds
                        if x < 0 or y < 0 or x >= new_w or y >= new_h:
                            # This will record the deletion for undo
                            self.apply_change(layer_name, key, None) 
                    except ValueError:
                        continue # Ignore non-coord keys
            
            # 3. Commit the entire resize as one action
            self.commit_action()
            
            # 4. Redraw and close
            self.draw_canvas()
            dialog.destroy()

        tk.Button(dialog, text="Apply", command=apply_resize).pack(pady=5)
        entry_h.bind('<Return>', lambda e: apply_resize())
    # --------------------------------

    def delete_map(self):
        """Delete the current map"""
        if not self.current_map_id:
            messagebox.showwarning("No Map", "No map selected")
            return
        
        if messagebox.askyesno("Delete Map", f"Delete map '{self.current_map_id}'? This will also delete the file ./maps/{self.current_map_id}.json"):
            # --- MODIFICATION: Use self.maps_data and delete file ---
            # Delete from memory
            del self.maps_data[self.current_map_id]
            
            # Delete file
            filename = f"{self.current_map_id}.json"
            filepath = os.path.join(self.maps_dir, filename)
            if os.path.exists(filepath):
                try:
                    os.remove(filepath)
                except Exception as e:
                    messagebox.showerror("Error", f"Could not delete map file: {e}")
            # ------------------------------------------------------
            
            self.current_map_id = None
            self.refresh_map_list()
            self.draw_canvas()
    
    def on_map_selected(self, event):
        """Handle map selection from dropdown"""
        # self.save_current_map() # <-- MODIFICATION: No longer needed
        self.current_map_id = self.map_var.get()
        self.load_current_map()
    
    def get_current_map_data(self):
        """Get the current map's data structure"""
        # --- MODIFICATION: Use self.maps_data ---
        if not self.current_map_id or self.current_map_id not in self.maps_data:
            return None
        return self.maps_data[self.current_map_id]
        # ----------------------------------------
    
    def load_current_map(self):
        """Load the current map's data"""
        map_data = self.get_current_map_data()
        if not map_data:
            return
            
        # --- Clear undo/redo history ---
        self.undo_stack = []
        self.redo_stack = []
        self.current_action = []
        self.clipboard_data = {}
        # --------------------------------
        
        # --- Reset visibility toggles to True ---
        for var in self.layer_visibility.values():
            var.set(True)
        # ----------------------------------------
        
        # Load tileset if specified
        if map_data.get("tileset"):
            self.tileset_path = map_data["tileset"]
            if os.path.exists(self.tileset_path):
                try:
                    self.load_tileset_from_path(self.tileset_path)
                except Exception as e:
                    messagebox.showwarning("Tileset Error", f"Could not load tileset: {str(e)}")
            else:
                # Handle missing tileset
                self.tileset_image = None
                self.tileset_tiles = []
                self.tileset_path = None
                # Optionally clear from map data
                map_data["tileset"] = None 

        else:
             # No tileset specified, clear current one
            self.tileset_image = None
            self.tileset_tiles = []
            self.tileset_path = None

        self.draw_tileset()
        self.draw_canvas()
        self.update_status()
    
    def save_current_map(self):
        """Save the current map's data (called when switching maps)"""
        # Data is already being modified in place, so no explicit save needed
        # This method is no longer called by on_map_selected
        pass
    
    def load_tileset(self):
        """Load a tileset image"""
        filename = filedialog.askopenfilename(
            title="Load Tileset",
            filetypes=[("Image files", "*.png *.jpg *.jpeg *.gif *.bmp")]
        )
        if filename:
            self.load_tileset_from_path(filename)
            
            # Save tileset path to current map
            map_data = self.get_current_map_data()
            if map_data:
                map_data["tileset"] = filename
                self.tileset_path = filename
    
    def load_tileset_from_path(self, filename):
        """Load tileset from a given path"""
        try:
            self.tileset_image = Image.open(filename)
            width, height = self.tileset_image.size
            
            # Extract tiles (stacked vertically, 32x32)
            self.tileset_tiles = []
            num_tiles = height // 32
            
            for i in range(num_tiles):
                tile = self.tileset_image.crop((0, i * 32, 32, (i + 1) * 32))
                self.tileset_tiles.append(tile)
            
            self.selected_tile = 0
            self.draw_tileset()
            # Don't show this message on map load, only on manual load
            # messagebox.showinfo("Success", f"Loaded {num_tiles} tiles from tileset")
        except Exception as e:
            messagebox.showerror("Error", f"Failed to load tileset: {str(e)}")
            self.tileset_image = None
            self.tileset_tiles = []
            self.tileset_path = None
    
    def draw_tileset(self):
        self.tileset_canvas.delete('all')
        
        # Check if current layer is a number layer
        if self.layer_types[self.current_layer] == 'number':
            # Draw number picker
            self.tileset_label.config(text="Number Picker")
            self.draw_number_picker()
        else:
            # Draw tileset
            self.tileset_label.config(text="Tileset")
            if not self.tileset_tiles:
                self.tileset_canvas.create_text(100, 50, text="Load a tileset\nfrom toolbar",
                                                fill='white', font=('Arial', 10), justify=tk.CENTER)
                return
            
            canvas_width = 200
            tile_display_size = 48
            padding = 5
            
            if not hasattr(self, 'tileset_photos'):
                self.tileset_photos = []
            
            # Ensure list is long enough
            while len(self.tileset_photos) < len(self.tileset_tiles):
                self.tileset_photos.append(None)
                
            for i, tile in enumerate(self.tileset_tiles):
                y = i * (tile_display_size + padding) + padding
                
                # Draw tile
                tile_photo = ImageTk.PhotoImage(tile.resize((tile_display_size, tile_display_size), Image.NEAREST))
                self.tileset_canvas.create_image(padding, y, image=tile_photo, anchor=tk.NW)
                # Keep reference
                self.tileset_photos[i] = tile_photo
                
                # Draw tile number
                self.tileset_canvas.create_text(padding + tile_display_size + 10, y + tile_display_size // 2,
                                                text=f"#{i}", fill='white', anchor=tk.W)
                
                # Highlight selected tile
                if i == self.selected_tile:
                    self.tileset_canvas.create_rectangle(padding - 2, y - 2,
                                                         padding + tile_display_size + 2,
                                                         y + tile_display_size + 2,
                                                         outline='yellow', width=3)
            
            self.tileset_canvas.config(scrollregion=self.tileset_canvas.bbox('all'))
    
    def draw_number_picker(self):
        """Draw a grid of numbers for number layers"""
        canvas_width = 230
        cell_size = 45
        cols = 4
        padding = 5
        
        # Draw numbers 0-99
        for i in range(100):
            row = i // cols
            col = i % cols
            
            x = col * cell_size + padding
            y = row * cell_size + padding
            
            # Draw cell background
            fill_color = '#4A5568' if i != self.selected_number else '#2D3748'
            self.tileset_canvas.create_rectangle(x, y, x + cell_size - 5, y + cell_size - 5,
                                                 fill=fill_color, outline='#718096', width=1)
            
            # Draw number
            text_color = 'yellow' if i == self.selected_number else 'white'
            self.tileset_canvas.create_text(x + (cell_size - 5) // 2, y + (cell_size - 5) // 2,
                                            text=str(i), fill=text_color, 
                                            font=('Arial', 12, 'bold' if i == self.selected_number else 'normal'))
        
        self.tileset_canvas.config(scrollregion=self.tileset_canvas.bbox('all'))
    
    def on_tileset_click(self, event):
        canvas_x = self.tileset_canvas.canvasx(event.x)
        canvas_y = self.tileset_canvas.canvasy(event.y)
        
        if self.layer_types[self.current_layer] == 'number':
            # Click on number picker
            cell_size = 45
            cols = 4
            padding = 5
            
            col = int((canvas_x - padding) // cell_size)
            row = int((canvas_y - padding) // cell_size)
            
            if col >= 0 and col < cols and row >= 0:
                number_index = row * cols + col
                if 0 <= number_index < 100:
                    self.selected_number = number_index
                    self.draw_tileset()
        else:
            # Click on tileset
            if not self.tileset_tiles:
                return
            
            tile_display_size = 48
            padding = 5
            
            tile_index = int(canvas_y // (tile_display_size + padding))
            if 0 <= tile_index < len(self.tileset_tiles):
                self.selected_tile = tile_index
                self.draw_tileset()
    
    def set_tool(self, tool):
        self.current_tool = tool
        self.tool_var.set(tool)
        self.update_status()
    
    def set_layer(self, layer):
        self.current_layer = layer
        self.layer_var.set(layer)
        self.draw_tileset()
        self.draw_canvas()
        self.update_status()
    
    def update_status(self):
        if not self.current_map_id:
            self.status_bar.config(text="No map selected")
        else:
            self.status_bar.config(text=f"Map: {self.current_map_id} | Layer: {self.current_layer} ({self.layer_types[self.current_layer]}) | Tool: {self.current_tool}")
    
    def get_grid_pos(self, canvas_x, canvas_y):
        scaled_size = self.grid_size * self.zoom
                
        # Prevent division by zero if zoom is 0
        if scaled_size == 0:
            return (0, 0)
            
        # Reverse the to_canvas calculation:
        # (map_x - min_x) * scaled_size = canvas_x
        # map_x = (canvas_x / scaled_size) + min_x
        
        x = int(canvas_x / scaled_size) + self.min_x
        y = int(canvas_y / scaled_size) + self.min_y
        return (x, y)
    
    def on_canvas_press_1(self, event):
        """Handle Left-click press."""
        if not self.current_map_id:
            return
        
        x = self.canvas.canvasx(event.x)
        y = self.canvas.canvasy(event.y)
        grid_x, grid_y = self.get_grid_pos(x, y)
        
        self.current_action = [] # Start a new action
        
        if self.current_tool == 'place':
            self.place_tile(grid_x, grid_y)
            self.draw_canvas()
        elif self.current_tool == 'erase':
            self.erase_tile(grid_x, grid_y)
            self.draw_canvas()
        elif self.current_tool == 'select':
            self.selection_start = (grid_x, grid_y)
    
    def on_canvas_drag(self, event):
        """Handle Left-click drag."""
        if not self.current_map_id:
            return
        
        x = self.canvas.canvasx(event.x)
        y = self.canvas.canvasy(event.y)
        grid_x, grid_y = self.get_grid_pos(x, y)
        
        if self.current_tool == 'place':
            self.place_tile(grid_x, grid_y) # Continues the current action
            self.draw_canvas()
        elif self.current_tool == 'erase':
            self.erase_tile(grid_x, grid_y) # Continues the current action
            self.draw_canvas()
        elif self.current_tool == 'select' and self.selection_start:
            # Draw selection rectangle
            if self.selection_rect:
                self.canvas.delete(self.selection_rect)
            
            start_x, start_y = self.selection_start
            scaled_size = self.grid_size * self.zoom
            
            # --- Need to use the min_x/min_y offset for drawing ---
            min_draw_x = (min(start_x, grid_x) - self.min_x) * scaled_size
            min_draw_y = (min(start_y, grid_y) - self.min_y) * scaled_size
            max_draw_x = (max(start_x, grid_x) + 1 - self.min_x) * scaled_size
            max_draw_y = (max(start_y, grid_y) + 1 - self.min_y) * scaled_size
            # -----------------------------------------------------
            
            self.selection_rect = self.canvas.create_rectangle(
                min_draw_x, min_draw_y, max_draw_x, max_draw_y, 
                outline='cyan', width=2, dash=(5, 5)
            )
    
    def on_canvas_release_1(self, event):
        """Handle Left-click release."""
        if self.current_tool == 'place' or self.current_tool == 'erase':
            self.commit_action() # Commit the drag/click action
        
        elif self.current_tool == 'select' and self.selection_start:
            x = self.canvas.canvasx(event.x)
            y = self.canvas.canvasy(event.y)
            grid_x, grid_y = self.get_grid_pos(x, y)
            
            start_x, start_y = self.selection_start
            
            # --- This is the "Copy" operation ---
            
            # --- MODIFICATION: Use helper ---
            min_x = min(start_x, grid_x)
            min_y = min(start_y, grid_y)
            max_x = max(start_x, grid_x)
            max_y = max(start_y, grid_y)
            
            copied_count = self._copy_selection_to_clipboard(min_x, max_x, min_y, max_y)
            if copied_count > 0:
                messagebox.showinfo("Copied", f"Copied {copied_count} tile entries to clipboard.\nUse Ctrl+V to paste.")
            else:
                messagebox.showinfo("Copied", "Copied empty selection to clipboard.")
            # ------------------------------------
            
            if self.selection_rect:
                self.canvas.delete(self.selection_rect)
                self.selection_rect = None
            self.selection_start = None
    
    def on_canvas_press_3(self, event):
        """Right-click press to erase"""
        if not self.current_map_id:
            return
        
        x = self.canvas.canvasx(event.x)
        y = self.canvas.canvasy(event.y)
        grid_x, grid_y = self.get_grid_pos(x, y)
        
        self.current_action = [] # Start new erase action
        self.erase_tile(grid_x, grid_y)
        self.draw_canvas()
    
    def on_canvas_right_drag(self, event):
        """Right-drag to erase"""
        if not self.current_map_id:
            return
        
        x = self.canvas.canvasx(event.x)
        y = self.canvas.canvasy(event.y)
        grid_x, grid_y = self.get_grid_pos(x, y)
        self.erase_tile(grid_x, grid_y) # Continues erase action
        self.draw_canvas()

    def on_canvas_release_3(self, event):
        """Right-click release"""
        self.commit_action() # Commit the erase action
    
    def on_canvas_motion(self, event):
        if not self.current_map_id:
            return

        x = self.canvas.canvasx(event.x)
        y = self.canvas.canvasy(event.y)
        grid_x, grid_y = self.get_grid_pos(x, y)

        self.current_grid_pos = (grid_x, grid_y) # Update cursor position

        # Show hover preview
        self.canvas.delete('hover')
        
        # --- ADDED: Only draw hover if inside map bounds ---
        map_data = self.get_current_map_data()
        if not map_data:
            return
        map_width = map_data.get("width", 20)
        map_height = map_data.get("height", 20)
        
        if grid_x < 0 or grid_x >= map_width or grid_y < 0 or grid_y >= map_height:
             return # Cursor is outside the map
        # ---------------------------------------------------
        
        scaled_size = self.grid_size * self.zoom

        # --- FIX: Apply the map offset to the drawing coordinates ---
        # This logic now matches the 'to_canvas' helper in draw_canvas
        x1 = (grid_x - self.min_x) * scaled_size
        y1 = (grid_y - self.min_y) * scaled_size
        x2 = (grid_x + 1 - self.min_x) * scaled_size
        y2 = (grid_y + 1 - self.min_y) * scaled_size
        # --------------------------------------------------------

        self.canvas.create_rectangle(
            x1, y1, x2, y2, # Use the corrected coordinates
            outline='white', width=1, dash=(2, 2), tags='hover'
        )
    
    def place_tile(self, x, y):
        map_data = self.get_current_map_data()
        if not map_data:
            return
        
        # --- ADDED: Bounds check ---
        map_width = map_data.get("width", 20)
        map_height = map_data.get("height", 20)
        if x < 0 or x >= map_width or y < 0 or y >= map_height:
            return # Don't place outside map
        # ---------------------------
        
        key = f"{x},{y}"
        
        if self.layer_types[self.current_layer] == 'tile':
            if not self.tileset_tiles:
                messagebox.showwarning("Warning", "Please load a tileset first")
                return
            value_to_place = self.selected_tile
        else:  # number layer
            value_to_place = self.selected_number
        
        self.apply_change(self.current_layer, key, value_to_place)
        # self.draw_canvas() # Moved to the calling function (press/drag)
    
    def erase_tile(self, x, y):
        map_data = self.get_current_map_data()
        if not map_data:
            return
            
        # --- ADDED: Bounds check ---
        map_width = map_data.get("width", 20)
        map_height = map_data.get("height", 20)
        if x < 0 or x >= map_width or y < 0 or y >= map_height:
            return # Don't erase outside map
        # ---------------------------
        
        key = f"{x},{y}"
        # We can just apply 'None' - apply_change will handle
        # checking if it already exists or not.
        self.apply_change(self.current_layer, key, None)
        # self.draw_canvas() # Moved to the calling function (press/drag)
    
    def draw_canvas(self):
        self.canvas.delete('all')
        
        map_data = self.get_current_map_data()
        if not map_data:
            self.canvas.create_text(400, 300, text="No map selected\nCreate or select a map from the toolbar",
                                    fill='white', font=('Arial', 14), justify=tk.CENTER)
            return
        
        # --- MODIFICATION: Get size from map data ---
        map_width = map_data.get("width", 20)
        map_height = map_data.get("height", 20)
        
        # Ensure older maps get updated if they load
        if "width" not in map_data:
            map_data["width"] = map_width
        if "height" not in map_data:
            map_data["height"] = map_height
        # --------------------------------------------
        
        # --- REMOVED DYNAMIC BOUNDS CALCULATION ---
        # all_positions = [] ...
        
        # --- MODIFICATION: Use map_width/height ---
        min_x, min_y = 0, 0
        max_x, max_y = map_width, map_height # Use map_width/height

        self.min_x = min_x
        self.min_y = min_y
        
        # Use a canvas size based on min/max
        scaled_size = self.grid_size * self.zoom
        canvas_width = (max_x - min_x) * scaled_size
        canvas_height = (max_y - min_y) * scaled_size
        # ------------------------------------------
        
        # Function to convert map coords to canvas coords
        def to_canvas(map_x, map_y):
            return (map_x - min_x) * scaled_size, (map_y - min_y) * scaled_size
            
        # Draw grid
        # --- MODIFIED: Draw grid lines based on map size ---
        # Draw a bounding box for the map
        self.canvas.create_rectangle(0, 0, canvas_width, canvas_height,
                                     outline='#888', width=1, dash=(4, 4))
                                     
        # Draw grid lines inside the box
        for x in range(min_x + 1, max_x): # +1 to max_x
            cx, _ = to_canvas(x, min_y)
            _, cy2 = to_canvas(x, max_y)
            self.canvas.create_line(cx, 0, cx, canvas_height,
                                    fill='#333333', width=1)
        for y in range(min_y + 1, max_y): # +1 to max_y
            _, cy = to_canvas(min_x, y)
            cx2, _ = to_canvas(max_x, y)
            self.canvas.create_line(0, cy, canvas_width, cy,
                                    fill='#333333', width=1)
        # ---------------------------------------------------
        
        # Draw layers in order
        if not hasattr(self, 'tile_photos'):
            self.tile_photos = {}
        # Clear old photo refs
        self.tile_photos.clear() 

        for layer_name in self.layer_order:
            
            # --- ADDED: Check layer visibility ---
            if not self.layer_visibility[layer_name].get():
                continue
            # -------------------------------------
            
            layer_data = map_data["layers"][layer_name]
            is_current = layer_name == self.current_layer
            
            for key, value in layer_data.items():
                try:
                    x, y = map(int, key.split(','))
                except ValueError:
                    continue # Skip bad key

                # --- ADDED: Don't draw tiles outside bounds (should be deleted but as a safety)
                if x < 0 or x >= map_width or y < 0 or y >= map_height:
                    continue
                # -----------------------------------------------------------------

                x1, y1 = to_canvas(x, y)
                x2, y2 = to_canvas(x + 1, y + 1)
                
                if self.layer_types[layer_name] == 'tile':
                    # Draw tile
                    if value < len(self.tileset_tiles):
                        tile = self.tileset_tiles[value]
                        size = int(scaled_size)
                        if size > 0:
                            tile_resized = tile.resize((size, size), Image.NEAREST)
                            tile_photo = ImageTk.PhotoImage(tile_resized)
                            
                            # Store reference
                            self.tile_photos[(x, y, layer_name)] = tile_photo
                            
                            self.canvas.create_image(x1, y1, image=tile_photo, anchor=tk.NW,
                                                     tags=f'layer_{layer_name}')
                else:
                    # Draw number
                    color = self.layer_colors.get(layer_name, '#FFFFFF')
                    # Use stipple for non-current layers to show transparency
                    stipple = '' if is_current else 'gray50'
                    
                    self.canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline='',
                                                 stipple=stipple,
                                                 tags=f'layer_{layer_name}')
                    self.canvas.create_text((x1 + x2) / 2, (y1 + y2) / 2,
                                            text=str(value), fill='black',
                                            font=('Arial', int(10 * self.zoom), 'bold'),
                                            tags=f'layer_{layer_name}')
        
        # --- MODIFIED: Set scrollregion to at least canvas size, or map size ---
        # This ensures you can scroll even if the map is smaller than the window
        visible_width = self.canvas.winfo_width()
        visible_height = self.canvas.winfo_height()
        
        scroll_w = max(canvas_width, visible_width)
        scroll_h = max(canvas_height, visible_height)
        
        self.canvas.config(scrollregion=(0, 0, scroll_w, scroll_h))
        # ----------------------------------------------------------------------
    
    def zoom_in(self):
        self.zoom = min(self.zoom * 1.5, 4.0)
        self.draw_canvas()
    
    def zoom_out(self):
        self.zoom = max(self.zoom / 1.5, 0.25)
        self.draw_canvas()
    
    def refresh(self):
        """Refresh the tab (called by main editor after reload)"""
        # Data is already reloaded by self.load_all_maps_from_files()
        # We just need to refresh the UI
        self.refresh_map_list()
        if self.current_map_id:
            self.load_current_map()
        else:
            # No map selected, just clear canvas
            self.draw_canvas()