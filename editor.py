import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import json
import os

class HeadersEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("Glass Eyes Editor")
        self.root.geometry("900x600")
        
        self.filename = "headers.json"
        self.data = self.load_data()
        
        # Create menu bar
        menubar = tk.Menu(root)
        root.config(menu=menubar)
        
        file_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="Save", command=self.save_data)
        file_menu.add_command(label="Reload", command=self.reload_data)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=root.quit)
        
        # Create notebook (tabbed interface)
        self.notebook = ttk.Notebook(root)
        self.notebook.pack(fill='both', expand=True, padx=5, pady=5)
        
        # Create tabs
        self.create_animations_tab()
        self.create_items_tab()
        self.create_objects_tab()
        self.create_cutscenes_tab()
        self.create_actions_tab()
        
    def load_data(self):
        """Load data from headers.json"""
        if os.path.exists(self.filename):
            with open(self.filename, 'r') as f:
                return json.load(f)
        else:
            return {
                "animations": {},
                "items": {},
                "objects": {},
                "cutscenes": {},
                "actions": {
                    "interactable": {},
                    "automatic": {}
                }
            }
    
    def save_data(self):
        """Save data to headers.json"""
        try:
            with open(self.filename, 'w') as f:
                json.dump(self.data, f, indent=4)
            messagebox.showinfo("Success", "File saved successfully!")
        except Exception as e:
            messagebox.showerror("Error", f"Failed to save file: {str(e)}")
    
    def reload_data(self):
        """Reload data from file"""
        self.data = self.load_data()
        self.refresh_all_tabs()
        messagebox.showinfo("Success", "Data reloaded!")
    
    def refresh_all_tabs(self):
        """Refresh all tab displays"""
        self.refresh_animations()
        self.refresh_items()
        self.refresh_objects()
        self.refresh_cutscenes()
        self.refresh_actions()
    
    # ANIMATIONS TAB
    def create_animations_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Animations")
        
        # Left panel - entity list
        left_frame = ttk.Frame(tab)
        left_frame.pack(side='left', fill='both', expand=True, padx=5, pady=5)
        
        ttk.Label(left_frame, text="Entities:", font=('Arial', 10, 'bold')).pack()
        
        self.anim_entity_listbox = tk.Listbox(left_frame, height=15)
        self.anim_entity_listbox.pack(fill='both', expand=True)
        self.anim_entity_listbox.bind('<<ListboxSelect>>', self.on_entity_select)
        
        btn_frame = ttk.Frame(left_frame)
        btn_frame.pack(fill='x', pady=5)
        ttk.Button(btn_frame, text="Add Entity", command=self.add_animation_entity).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Delete Entity", command=self.delete_animation_entity).pack(side='left', padx=2)
        
        # Right panel - animation list
        right_frame = ttk.Frame(tab)
        right_frame.pack(side='right', fill='both', expand=True, padx=5, pady=5)
        
        ttk.Label(right_frame, text="Animations:", font=('Arial', 10, 'bold')).pack()
        
        self.anim_listbox = tk.Listbox(right_frame, height=15)
        self.anim_listbox.pack(fill='both', expand=True)
        
        btn_frame2 = ttk.Frame(right_frame)
        btn_frame2.pack(fill='x', pady=5)
        ttk.Button(btn_frame2, text="Add Animation", command=self.add_animation).pack(side='left', padx=2)
        ttk.Button(btn_frame2, text="Edit Animation", command=self.edit_animation).pack(side='left', padx=2)
        ttk.Button(btn_frame2, text="Delete Animation", command=self.delete_animation).pack(side='left', padx=2)
        
        self.refresh_animations()
    
    def refresh_animations(self):
        self.anim_entity_listbox.delete(0, tk.END)
        for entity in self.data.get('animations', {}).keys():
            self.anim_entity_listbox.insert(tk.END, entity)
    
    def on_entity_select(self, event):
        selection = self.anim_entity_listbox.curselection()
        if selection:
            entity = self.anim_entity_listbox.get(selection[0])
            self.anim_listbox.delete(0, tk.END)
            for anim_name in self.data['animations'][entity].keys():
                self.anim_listbox.insert(tk.END, anim_name)
    
    def add_animation_entity(self):
        entity = simpledialog.askstring("Add Entity", "Enter entity name:")
        if entity:
            if entity in self.data['animations']:
                messagebox.showwarning("Warning", "Entity already exists!")
            else:
                self.data['animations'][entity] = {}
                self.refresh_animations()
    
    def delete_animation_entity(self):
        selection = self.anim_entity_listbox.curselection()
        if selection:
            entity = self.anim_entity_listbox.get(selection[0])
            if messagebox.askyesno("Confirm", f"Delete entity '{entity}' and all its animations?"):
                del self.data['animations'][entity]
                self.refresh_animations()
                self.anim_listbox.delete(0, tk.END)
    
    def add_animation(self):
        selection = self.anim_entity_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an entity first!")
            return
        
        entity = self.anim_entity_listbox.get(selection[0])
        self.edit_animation_dialog(entity, None)
    
    def edit_animation(self):
        entity_sel = self.anim_entity_listbox.curselection()
        anim_sel = self.anim_listbox.curselection()
        
        if not entity_sel or not anim_sel:
            messagebox.showwarning("Warning", "Please select an animation to edit!")
            return
        
        entity = self.anim_entity_listbox.get(entity_sel[0])
        anim_name = self.anim_listbox.get(anim_sel[0])
        self.edit_animation_dialog(entity, anim_name)
    
    def edit_animation_dialog(self, entity, anim_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Animation" if anim_name else "Add Animation")
        dialog.geometry("400x300")
        
        # Animation name
        ttk.Label(dialog, text="Animation Name:").grid(row=0, column=0, sticky='w', padx=5, pady=5)
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)
        
        # Frames
        ttk.Label(dialog, text="Frames (comma-separated):").grid(row=1, column=0, sticky='w', padx=5, pady=5)
        frames_entry = ttk.Entry(dialog, width=30)
        frames_entry.grid(row=1, column=1, padx=5, pady=5)
        
        # Speed
        ttk.Label(dialog, text="Speed:").grid(row=2, column=0, sticky='w', padx=5, pady=5)
        speed_entry = ttk.Entry(dialog, width=30)
        speed_entry.grid(row=2, column=1, padx=5, pady=5)
        
        # Loop
        ttk.Label(dialog, text="Loop:").grid(row=3, column=0, sticky='w', padx=5, pady=5)
        loop_var = tk.BooleanVar()
        loop_check = ttk.Checkbutton(dialog, variable=loop_var)
        loop_check.grid(row=3, column=1, sticky='w', padx=5, pady=5)
        
        # Populate if editing
        if anim_name:
            anim_data = self.data['animations'][entity][anim_name]
            name_entry.insert(0, anim_name)
            frames_entry.insert(0, ','.join(map(str, anim_data['frames'])))
            speed_entry.insert(0, str(anim_data['speed']))
            loop_var.set(anim_data['loop'])
        
        def save_animation():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Animation name cannot be empty!")
                return
            
            try:
                frames = [int(x.strip()) for x in frames_entry.get().split(',')]
                speed = int(speed_entry.get())
            except ValueError:
                messagebox.showerror("Error", "Invalid frames or speed value!")
                return
            
            # If renaming, delete old entry
            if anim_name and anim_name != new_name:
                del self.data['animations'][entity][anim_name]
            
            self.data['animations'][entity][new_name] = {
                "frames": frames,
                "speed": speed,
                "loop": loop_var.get()
            }
            
            self.on_entity_select(None)
            dialog.destroy()
        
        ttk.Button(dialog, text="Save", command=save_animation).grid(row=4, column=0, columnspan=2, pady=20)
    
    def delete_animation(self):
        entity_sel = self.anim_entity_listbox.curselection()
        anim_sel = self.anim_listbox.curselection()
        
        if not entity_sel or not anim_sel:
            messagebox.showwarning("Warning", "Please select an animation to delete!")
            return
        
        entity = self.anim_entity_listbox.get(entity_sel[0])
        anim_name = self.anim_listbox.get(anim_sel[0])
        
        if messagebox.askyesno("Confirm", f"Delete animation '{anim_name}'?"):
            del self.data['animations'][entity][anim_name]
            self.on_entity_select(None)
    
    # ITEMS TAB
    def create_items_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Items")
        
        ttk.Label(tab, text="Items:", font=('Arial', 10, 'bold')).pack(pady=5)
        
        self.items_listbox = tk.Listbox(tab, height=20)
        self.items_listbox.pack(fill='both', expand=True, padx=5)
        
        btn_frame = ttk.Frame(tab)
        btn_frame.pack(fill='x', padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Item", command=self.add_item).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Edit Item", command=self.edit_item).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Delete Item", command=self.delete_item).pack(side='left', padx=2)
        
        self.refresh_items()
    
    def refresh_items(self):
        self.items_listbox.delete(0, tk.END)
        for item in self.data.get('items', {}).keys():
            props = self.data['items'][item]
            display = f"{item}" + (f" (drop: {props.get('drop')})" if props.get('drop') is not None else "")
            self.items_listbox.insert(tk.END, display)
    
    def add_item(self):
        self.edit_item_dialog(None)
    
    def edit_item(self):
        selection = self.items_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an item to edit!")
            return
        
        item_display = self.items_listbox.get(selection[0])
        item_name = item_display.split(' (')[0]
        self.edit_item_dialog(item_name)
    
    def edit_item_dialog(self, item_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Item" if item_name else "Add Item")
        dialog.geometry("350x150")
        
        ttk.Label(dialog, text="Item Name:").grid(row=0, column=0, sticky='w', padx=5, pady=5)
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Drop:").grid(row=1, column=0, sticky='w', padx=5, pady=5)
        drop_var = tk.BooleanVar()
        drop_check = ttk.Checkbutton(dialog, variable=drop_var)
        drop_check.grid(row=1, column=1, sticky='w', padx=5, pady=5)
        
        if item_name:
            name_entry.insert(0, item_name)
            if 'drop' in self.data['items'][item_name]:
                drop_var.set(self.data['items'][item_name]['drop'])
        
        def save_item():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Item name cannot be empty!")
                return
            
            if item_name and item_name != new_name:
                del self.data['items'][item_name]
            
            item_data = {}
            if drop_var.get():
                item_data['drop'] = True
            
            self.data['items'][new_name] = item_data
            self.refresh_items()
            dialog.destroy()
        
        ttk.Button(dialog, text="Save", command=save_item).grid(row=2, column=0, columnspan=2, pady=20)
    
    def delete_item(self):
        selection = self.items_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an item to delete!")
            return
        
        item_display = self.items_listbox.get(selection[0])
        item_name = item_display.split(' (')[0]
        
        if messagebox.askyesno("Confirm", f"Delete item '{item_name}'?"):
            del self.data['items'][item_name]
            self.refresh_items()
    
    # OBJECTS TAB
    def create_objects_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Objects")
        
        ttk.Label(tab, text="Objects:", font=('Arial', 10, 'bold')).pack(pady=5)
        
        self.objects_listbox = tk.Listbox(tab, height=20)
        self.objects_listbox.pack(fill='both', expand=True, padx=5)
        
        btn_frame = ttk.Frame(tab)
        btn_frame.pack(fill='x', padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Object", command=self.add_object).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Edit Object", command=self.edit_object).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Delete Object", command=self.delete_object).pack(side='left', padx=2)
        
        self.refresh_objects()
    
    def refresh_objects(self):
        self.objects_listbox.delete(0, tk.END)
        for obj in self.data.get('objects', {}).keys():
            props = self.data['objects'][obj]
            details = []
            if 'follow' in props:
                details.append(f"follow: {props['follow']}")
            if 'idle_animation' in props:
                details.append(f"idle: {props['idle_animation']}")
            if 'is_pressed' in props:
                details.append(f"pressed: {props['is_pressed']}")
            
            display = f"{obj}" + (f" ({', '.join(details)})" if details else "")
            self.objects_listbox.insert(tk.END, display)
    
    def add_object(self):
        self.edit_object_dialog(None)
    
    def edit_object(self):
        selection = self.objects_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an object to edit!")
            return
        
        obj_display = self.objects_listbox.get(selection[0])
        obj_name = obj_display.split(' (')[0]
        self.edit_object_dialog(obj_name)
    
    def edit_object_dialog(self, obj_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Object" if obj_name else "Add Object")
        dialog.geometry("400x250")
        
        ttk.Label(dialog, text="Object Name:").grid(row=0, column=0, sticky='w', padx=5, pady=5)
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Follow:").grid(row=1, column=0, sticky='w', padx=5, pady=5)
        follow_entry = ttk.Entry(dialog, width=30)
        follow_entry.grid(row=1, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Idle Animation:").grid(row=2, column=0, sticky='w', padx=5, pady=5)
        idle_entry = ttk.Entry(dialog, width=30)
        idle_entry.grid(row=2, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Is Pressed:").grid(row=3, column=0, sticky='w', padx=5, pady=5)
        pressed_var = tk.BooleanVar()
        pressed_check = ttk.Checkbutton(dialog, variable=pressed_var)
        pressed_check.grid(row=3, column=1, sticky='w', padx=5, pady=5)
        
        if obj_name:
            obj_data = self.data['objects'][obj_name]
            name_entry.insert(0, obj_name)
            if 'follow' in obj_data:
                follow_entry.insert(0, obj_data['follow'])
            if 'idle_animation' in obj_data:
                idle_entry.insert(0, obj_data['idle_animation'])
            if 'is_pressed' in obj_data:
                pressed_var.set(obj_data['is_pressed'])
        
        def save_object():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Object name cannot be empty!")
                return
            
            if obj_name and obj_name != new_name:
                del self.data['objects'][obj_name]
            
            obj_data = {}
            if follow_entry.get().strip():
                obj_data['follow'] = follow_entry.get().strip()
            if idle_entry.get().strip():
                obj_data['idle_animation'] = idle_entry.get().strip()
            if pressed_var.get():
                obj_data['is_pressed'] = True
            
            self.data['objects'][new_name] = obj_data
            self.refresh_objects()
            dialog.destroy()
        
        ttk.Button(dialog, text="Save", command=save_object).grid(row=4, column=0, columnspan=2, pady=20)
    
    def delete_object(self):
        selection = self.objects_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an object to delete!")
            return
        
        obj_display = self.objects_listbox.get(selection[0])
        obj_name = obj_display.split(' (')[0]
        
        if messagebox.askyesno("Confirm", f"Delete object '{obj_name}'?"):
            del self.data['objects'][obj_name]
            self.refresh_objects()
    
    # CUTSCENES TAB
    def create_cutscenes_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Cutscenes")
        
        ttk.Label(tab, text="Cutscenes:", font=('Arial', 10, 'bold')).pack(pady=5)
        
        self.cutscenes_listbox = tk.Listbox(tab, height=20)
        self.cutscenes_listbox.pack(fill='both', expand=True, padx=5)
        
        btn_frame = ttk.Frame(tab)
        btn_frame.pack(fill='x', padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Cutscene", command=self.add_cutscene).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Edit Cutscene", command=self.edit_cutscene).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Delete Cutscene", command=self.delete_cutscene).pack(side='left', padx=2)
        
        self.refresh_cutscenes()
    
    def refresh_cutscenes(self):
        self.cutscenes_listbox.delete(0, tk.END)
        for cutscene in self.data.get('cutscenes', {}).keys():
            props = self.data['cutscenes'][cutscene]
            details = []
            if 'type' in props:
                details.append(f"type: {props['type']}")
            if 'music' in props:
                details.append(f"music: {props['music']}")
            
            display = f"{cutscene}" + (f" ({', '.join(details)})" if details else "")
            self.cutscenes_listbox.insert(tk.END, display)
    
    def add_cutscene(self):
        self.edit_cutscene_dialog(None)
    
    def edit_cutscene(self):
        selection = self.cutscenes_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select a cutscene to edit!")
            return
        
        cutscene_display = self.cutscenes_listbox.get(selection[0])
        cutscene_name = cutscene_display.split(' (')[0]
        self.edit_cutscene_dialog(cutscene_name)
    
    def edit_cutscene_dialog(self, cutscene_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Cutscene" if cutscene_name else "Add Cutscene")
        dialog.geometry("400x300")
        
        ttk.Label(dialog, text="Cutscene Name:").grid(row=0, column=0, sticky='w', padx=5, pady=5)
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Conversation:").grid(row=1, column=0, sticky='w', padx=5, pady=5)
        conv_entry = ttk.Entry(dialog, width=30)
        conv_entry.grid(row=1, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Music:").grid(row=2, column=0, sticky='w', padx=5, pady=5)
        music_entry = ttk.Entry(dialog, width=30)
        music_entry.grid(row=2, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Type:").grid(row=3, column=0, sticky='w', padx=5, pady=5)
        type_entry = ttk.Entry(dialog, width=30)
        type_entry.grid(row=3, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="Background:").grid(row=4, column=0, sticky='w', padx=5, pady=5)
        bg_entry = ttk.Entry(dialog, width=30)
        bg_entry.grid(row=4, column=1, padx=5, pady=5)
        
        ttk.Label(dialog, text="SFX:").grid(row=5, column=0, sticky='w', padx=5, pady=5)
        sfx_entry = ttk.Entry(dialog, width=30)
        sfx_entry.grid(row=5, column=1, padx=5, pady=5)
        
        if cutscene_name:
            cutscene_data = self.data['cutscenes'][cutscene_name]
            name_entry.insert(0, cutscene_name)
            if 'conversation' in cutscene_data:
                conv_entry.insert(0, cutscene_data['conversation'])
            if 'music' in cutscene_data:
                music_entry.insert(0, str(cutscene_data['music']))
            if 'type' in cutscene_data:
                type_entry.insert(0, cutscene_data['type'])
            if 'bg' in cutscene_data:
                bg_entry.insert(0, cutscene_data['bg'])
            if 'sfx' in cutscene_data:
                sfx_entry.insert(0, cutscene_data['sfx'])
        
        def save_cutscene():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Cutscene name cannot be empty!")
                return
            
            if cutscene_name and cutscene_name != new_name:
                del self.data['cutscenes'][cutscene_name]
            
            cutscene_data = {}
            if conv_entry.get().strip():
                cutscene_data['conversation'] = conv_entry.get().strip()
            if music_entry.get().strip():
                music_val = music_entry.get().strip()
                if music_val.lower() == 'false':
                    cutscene_data['music'] = False
                else:
                    cutscene_data['music'] = music_val
            if type_entry.get().strip():
                cutscene_data['type'] = type_entry.get().strip()
            if bg_entry.get().strip():
                cutscene_data['bg'] = bg_entry.get().strip()
            if sfx_entry.get().strip():
                cutscene_data['sfx'] = sfx_entry.get().strip()
            
            self.data['cutscenes'][new_name] = cutscene_data
            self.refresh_cutscenes()
            dialog.destroy()
        
        ttk.Button(dialog, text="Save", command=save_cutscene).grid(row=6, column=0, columnspan=2, pady=20)
    
    def delete_cutscene(self):
        selection = self.cutscenes_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select a cutscene to delete!")
            return
        
        cutscene_display = self.cutscenes_listbox.get(selection[0])
        cutscene_name = cutscene_display.split(' (')[0]
        
        if messagebox.askyesno("Confirm", f"Delete cutscene '{cutscene_name}'?"):
            del self.data['cutscenes'][cutscene_name]
            self.refresh_cutscenes()
    
    # ACTIONS TAB
    def create_actions_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Actions")
        
        # Top frame for action type selection
        top_frame = ttk.Frame(tab)
        top_frame.pack(fill='x', padx=5, pady=5)
        
        ttk.Label(top_frame, text="Action Type:", font=('Arial', 10, 'bold')).pack(side='left', padx=5)
        
        self.action_type_var = tk.StringVar(value="interactable")
        ttk.Radiobutton(top_frame, text="Interactable", variable=self.action_type_var, 
                       value="interactable", command=self.refresh_actions).pack(side='left', padx=5)
        ttk.Radiobutton(top_frame, text="Automatic", variable=self.action_type_var, 
                       value="automatic", command=self.refresh_actions).pack(side='left', padx=5)
        
        # Action list
        ttk.Label(tab, text="Actions:", font=('Arial', 10, 'bold')).pack(pady=5)
        
        self.actions_listbox = tk.Listbox(tab, height=20)
        self.actions_listbox.pack(fill='both', expand=True, padx=5)
        
        # Buttons
        btn_frame = ttk.Frame(tab)
        btn_frame.pack(fill='x', padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Action", command=self.add_action).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Edit Action", command=self.edit_action).pack(side='left', padx=2)
        ttk.Button(btn_frame, text="Delete Action", command=self.delete_action).pack(side='left', padx=2)
        
        self.refresh_actions()
    
    def refresh_actions(self):
        """Refresh the actions listbox based on selected action type"""
        self.actions_listbox.delete(0, tk.END)
        
        if 'actions' not in self.data:
            self.data['actions'] = {"interactable": {}, "automatic": {}}
        
        action_type = self.action_type_var.get()
        actions = self.data['actions'].get(action_type, {})
        
        for action_id in sorted(actions.keys(), key=lambda x: int(x)):
            props = actions[action_id]
            details = []
            
            if 'auto' in props:
                details.append(f"auto: {props['auto']}")
            if 'sequence' in props:
                details.append(f"seq: {len(props['sequence'])} items")
            if 'stage' in props:
                details.append(f"stage: {props['stage']}")
            if 'music' in props:
                details.append(f"music: {props['music']}")
            if 'new_map' in props:
                details.append(f"new_map: {props['new_map'].get('map', 'N/A')}")
            
            display = f"ID {action_id}" + (f" ({', '.join(details)})" if details else "")
            self.actions_listbox.insert(tk.END, display)
    
    def add_action(self):
        self.edit_action_dialog(None)
    
    def edit_action(self):
        selection = self.actions_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an action to edit!")
            return
        
        action_display = self.actions_listbox.get(selection[0])
        action_id = action_display.split(' (')[0].replace('ID ', '')
        self.edit_action_dialog(action_id)
    
    def edit_action_dialog(self, action_id):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Action" if action_id else "Add Action")
        dialog.geometry("600x650")
        
        # Make dialog scrollable
        canvas = tk.Canvas(dialog)
        scrollbar = ttk.Scrollbar(dialog, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)
        
        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )
        
        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        
        row = 0
        
        # Action ID
        ttk.Label(scrollable_frame, text="Action ID:").grid(row=row, column=0, sticky='w', padx=5, pady=5)
        id_entry = ttk.Entry(scrollable_frame, width=40)
        id_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # Sequence
        ttk.Label(scrollable_frame, text="Sequence (comma-separated):").grid(row=row, column=0, sticky='nw', padx=5, pady=5)
        sequence_entry = ttk.Entry(scrollable_frame, width=40)
        sequence_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # Auto
        ttk.Label(scrollable_frame, text="Auto:").grid(row=row, column=0, sticky='w', padx=5, pady=5)
        auto_entry = ttk.Entry(scrollable_frame, width=40)
        auto_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # Stage
        ttk.Label(scrollable_frame, text="Stage:").grid(row=row, column=0, sticky='w', padx=5, pady=5)
        stage_entry = ttk.Entry(scrollable_frame, width=40)
        stage_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # Music
        ttk.Label(scrollable_frame, text="Music:").grid(row=row, column=0, sticky='w', padx=5, pady=5)
        music_entry = ttk.Entry(scrollable_frame, width=40)
        music_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # New Map section
        ttk.Separator(scrollable_frame, orient='horizontal').grid(row=row, column=0, columnspan=2, sticky='ew', pady=10)
        row += 1
        
        ttk.Label(scrollable_frame, text="New Map Properties:", font=('Arial', 9, 'bold')).grid(row=row, column=0, columnspan=2, sticky='w', padx=5, pady=5)
        row += 1
        
        # Map
        ttk.Label(scrollable_frame, text="Map:").grid(row=row, column=0, sticky='w', padx=5, pady=5)
        map_entry = ttk.Entry(scrollable_frame, width=40)
        map_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # BG Track
        ttk.Label(scrollable_frame, text="BG Track:").grid(row=row, column=0, sticky='w', padx=5, pady=5)
        bg_track_entry = ttk.Entry(scrollable_frame, width=40)
        bg_track_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # BG
        ttk.Label(scrollable_frame, text="BG:").grid(row=row, column=0, sticky='w', padx=5, pady=5)
        bg_entry = ttk.Entry(scrollable_frame, width=40)
        bg_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1
        
        # Positions editor
        ttk.Separator(scrollable_frame, orient='horizontal').grid(row=row, column=0, columnspan=2, sticky='ew', pady=10)
        row += 1
        
        ttk.Label(scrollable_frame, text="Entity Positions:", font=('Arial', 9, 'bold')).grid(row=row, column=0, columnspan=2, sticky='w', padx=5, pady=5)
        row += 1
        
        positions_frame = ttk.Frame(scrollable_frame)
        positions_frame.grid(row=row, column=0, columnspan=2, padx=5, pady=5, sticky='ew')
        
        positions_listbox = tk.Listbox(positions_frame, height=6, width=50)
        positions_listbox.pack(side='left', fill='both', expand=True)
        
        positions_scroll = ttk.Scrollbar(positions_frame, orient='vertical', command=positions_listbox.yview)
        positions_scroll.pack(side='right', fill='y')
        positions_listbox.config(yscrollcommand=positions_scroll.set)
        
        # Store positions data in a dictionary
        positions_data = {}
        
        def refresh_positions_list():
            positions_listbox.delete(0, tk.END)
            for entity, coords in sorted(positions_data.items()):
                positions_listbox.insert(tk.END, f"{entity}: [{coords[0]}, {coords[1]}]")
        
        def add_position():
            pos_dialog = tk.Toplevel(dialog)
            pos_dialog.title("Add Position")
            pos_dialog.geometry("300x150")
            
            ttk.Label(pos_dialog, text="Entity Name:").grid(row=0, column=0, sticky='w', padx=5, pady=5)
            entity_entry = ttk.Entry(pos_dialog, width=20)
            entity_entry.grid(row=0, column=1, padx=5, pady=5)
            
            ttk.Label(pos_dialog, text="X Coordinate:").grid(row=1, column=0, sticky='w', padx=5, pady=5)
            x_entry = ttk.Entry(pos_dialog, width=20)
            x_entry.grid(row=1, column=1, padx=5, pady=5)
            
            ttk.Label(pos_dialog, text="Y Coordinate:").grid(row=2, column=0, sticky='w', padx=5, pady=5)
            y_entry = ttk.Entry(pos_dialog, width=20)
            y_entry.grid(row=2, column=1, padx=5, pady=5)
            
            def save_position():
                entity = entity_entry.get().strip()
                if not entity:
                    messagebox.showwarning("Warning", "Entity name cannot be empty!")
                    return
                
                try:
                    x = int(x_entry.get())
                    y = int(y_entry.get())
                except ValueError:
                    messagebox.showerror("Error", "Coordinates must be integers!")
                    return
                
                positions_data[entity] = [x, y]
                refresh_positions_list()
                pos_dialog.destroy()
            
            ttk.Button(pos_dialog, text="Save", command=save_position).grid(row=3, column=0, columnspan=2, pady=10)
        
        def edit_position():
            selection = positions_listbox.curselection()
            if not selection:
                messagebox.showwarning("Warning", "Please select a position to edit!")
                return
            
            selected_text = positions_listbox.get(selection[0])
            entity = selected_text.split(':')[0].strip()
            coords = positions_data[entity]
            
            pos_dialog = tk.Toplevel(dialog)
            pos_dialog.title("Edit Position")
            pos_dialog.geometry("300x150")
            
            ttk.Label(pos_dialog, text="Entity Name:").grid(row=0, column=0, sticky='w', padx=5, pady=5)
            entity_entry = ttk.Entry(pos_dialog, width=20)
            entity_entry.grid(row=0, column=1, padx=5, pady=5)
            entity_entry.insert(0, entity)
            
            ttk.Label(pos_dialog, text="X Coordinate:").grid(row=1, column=0, sticky='w', padx=5, pady=5)
            x_entry = ttk.Entry(pos_dialog, width=20)
            x_entry.grid(row=1, column=1, padx=5, pady=5)
            x_entry.insert(0, str(coords[0]))
            
            ttk.Label(pos_dialog, text="Y Coordinate:").grid(row=2, column=0, sticky='w', padx=5, pady=5)
            y_entry = ttk.Entry(pos_dialog, width=20)
            y_entry.grid(row=2, column=1, padx=5, pady=5)
            y_entry.insert(0, str(coords[1]))
            
            def save_position():
                new_entity = entity_entry.get().strip()
                if not new_entity:
                    messagebox.showwarning("Warning", "Entity name cannot be empty!")
                    return
                
                try:
                    x = int(x_entry.get())
                    y = int(y_entry.get())
                except ValueError:
                    messagebox.showerror("Error", "Coordinates must be integers!")
                    return
                
                # If entity name changed, delete old entry
                if entity != new_entity:
                    del positions_data[entity]
                
                positions_data[new_entity] = [x, y]
                refresh_positions_list()
                pos_dialog.destroy()
            
            ttk.Button(pos_dialog, text="Save", command=save_position).grid(row=3, column=0, columnspan=2, pady=10)
        
        def delete_position():
            selection = positions_listbox.curselection()
            if not selection:
                messagebox.showwarning("Warning", "Please select a position to delete!")
                return
            
            selected_text = positions_listbox.get(selection[0])
            entity = selected_text.split(':')[0].strip()
            
            if messagebox.askyesno("Confirm", f"Delete position for '{entity}'?"):
                del positions_data[entity]
                refresh_positions_list()
        
        row += 1
        
        positions_btn_frame = ttk.Frame(scrollable_frame)
        positions_btn_frame.grid(row=row, column=0, columnspan=2, pady=5)
        ttk.Button(positions_btn_frame, text="Add Position", command=add_position).pack(side='left', padx=2)
        ttk.Button(positions_btn_frame, text="Edit Position", command=edit_position).pack(side='left', padx=2)
        ttk.Button(positions_btn_frame, text="Delete Position", command=delete_position).pack(side='left', padx=2)
        row += 1
        
        # Populate if editing
        if action_id:
            action_type = self.action_type_var.get()
            action_data = self.data['actions'][action_type][action_id]
            
            id_entry.insert(0, action_id)
            id_entry.config(state='readonly')  # Don't allow changing ID when editing
            
            if 'sequence' in action_data:
                sequence_entry.insert(0, ', '.join(action_data['sequence']))
            if 'auto' in action_data:
                auto_entry.insert(0, action_data['auto'])
            if 'stage' in action_data:
                stage_entry.insert(0, action_data['stage'])
            if 'music' in action_data:
                music_entry.insert(0, action_data['music'])
            
            if 'new_map' in action_data:
                new_map = action_data['new_map']
                if 'map' in new_map:
                    map_entry.insert(0, new_map['map'])
                if 'bg_track' in new_map:
                    bg_track_entry.insert(0, new_map['bg_track'])
                if 'bg' in new_map:
                    bg_entry.insert(0, new_map['bg'])
                if 'positions' in new_map:
                    positions_data.update(new_map['positions'])
                    refresh_positions_list()
        
        def save_action():
            new_id = id_entry.get().strip()
            if not new_id:
                messagebox.showwarning("Warning", "Action ID cannot be empty!")
                return
            
            try:
                int(new_id)  # Validate ID is numeric
            except ValueError:
                messagebox.showerror("Error", "Action ID must be a number!")
                return
            
            action_type = self.action_type_var.get()
            
            # If changing ID, delete old entry
            if action_id and action_id != new_id:
                del self.data['actions'][action_type][action_id]
            
            action_data = {}
            
            # Add simple string fields
            if sequence_entry.get().strip():
                action_data['sequence'] = [s.strip() for s in sequence_entry.get().split(',')]
            if auto_entry.get().strip():
                action_data['auto'] = auto_entry.get().strip()
            if stage_entry.get().strip():
                action_data['stage'] = stage_entry.get().strip()
            if music_entry.get().strip():
                action_data['music'] = music_entry.get().strip()
            
            # Handle new_map object
            new_map = {}
            if map_entry.get().strip():
                new_map['map'] = map_entry.get().strip()
            if bg_track_entry.get().strip():
                new_map['bg_track'] = bg_track_entry.get().strip()
            if bg_entry.get().strip():
                new_map['bg'] = bg_entry.get().strip()
            
            if positions_data:
                new_map['positions'] = positions_data.copy()
            
            if new_map:
                action_data['new_map'] = new_map
            
            # Only save if there's actual data
            if not action_data:
                messagebox.showwarning("Warning", "Action must have at least one property!")
                return
            
            self.data['actions'][action_type][new_id] = action_data
            self.refresh_actions()
            dialog.destroy()
        
        # Save button at the bottom
        ttk.Button(scrollable_frame, text="Save", command=save_action).grid(row=row, column=0, columnspan=2, pady=20)
        
        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")
    
    def delete_action(self):
        selection = self.actions_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an action to delete!")
            return
        
        action_display = self.actions_listbox.get(selection[0])
        action_id = action_display.split(' (')[0].replace('ID ', '')
        action_type = self.action_type_var.get()
        
        if messagebox.askyesno("Confirm", f"Delete action ID '{action_id}'?"):
            del self.data['actions'][action_type][action_id]
            self.refresh_actions()

if __name__ == "__main__":
    root = tk.Tk()
    app = HeadersEditor(root)
    root.mainloop()