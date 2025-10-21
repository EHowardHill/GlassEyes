import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import json  # <-- Added import


class DialogueTab:
    def __init__(self, notebook, app):
        self.app = app
        self.root = app.root
        self.dialogue_data = app.get_dialogue_data()

        self.branching1_combo = None
        self.branching2_combo = None

        self.load_constants()  # <-- Load constants on initialization

        self.frame = ttk.Frame(notebook)
        notebook.add(self.frame, text="Dialogue")

        self.create_widgets()
        self.refresh()

    def load_constants(self):
        """Loads and processes constants from constants.json for dropdowns."""
        self.constant_options = {}
        try:
            with open("constants.json", "r") as f:
                const_data = json.load(f)

            # Process emotions
            emotions = [""]  # Start with an empty option
            for emotion in const_data.get("emotions", []):
                fixed = emotion.replace(" ", "_").upper()
                emotions.append("EM_" + fixed)
            self.constant_options["emotion"] = emotions

            # Process actions
            actions = [""]
            for action in const_data.get("actions", []):
                fixed = action.replace(" ", "_").upper()
                actions.append("ACT_" + fixed)
            self.constant_options["action"] = actions

            # Process speed
            speeds = [""]
            for speed in const_data.get("speed", []):
                fixed = speed.replace(" ", "_").upper()
                speeds.append("SP_" + fixed)
            self.constant_options["speed"] = speeds

            # Process size
            sizes = [""]
            for size in const_data.get("size", []):
                fixed = size.replace(" ", "_").upper()
                sizes.append(fixed)
            self.constant_options["size"] = sizes

            # Process colors
            colors = [""]
            for color in const_data.get("colors", []):
                fixed = color.replace(" ", "_").upper()
                # The JSON data already has the "COLOR_" prefix
                colors.append(fixed)
            self.constant_options["color"] = colors

        except FileNotFoundError:
            messagebox.showerror("Error", "constants.json not found.")
            # Populate with empty lists to avoid errors
            self.constant_options = {
                "emotion": [""],
                "action": [""],
                "speed": [""],
                "size": [""],
                "color": [""],
            }
        except json.JSONDecodeError:
            messagebox.showerror("Error", "Failed to parse constants.json.")
            self.constant_options = {
                "emotion": [""],
                "action": [""],
                "speed": [""],
                "size": [""],
                "color": [""],
            }

    def create_widgets(self):
        # Main container
        main_frame = ttk.Frame(self.frame)
        main_frame.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        # Left panel - Conversation list
        left_frame = ttk.Frame(main_frame, width=250)
        left_frame.pack(side=tk.LEFT, fill=tk.BOTH, padx=(0, 5))

        ttk.Label(left_frame, text="Conversations", font=("Arial", 12, "bold")).pack(
            pady=5
        )

        conv_scroll = ttk.Scrollbar(left_frame)
        conv_scroll.pack(side=tk.RIGHT, fill=tk.Y)

        self.conv_listbox = tk.Listbox(
            left_frame, yscrollcommand=conv_scroll.set, font=("Arial", 10)
        )
        self.conv_listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.conv_listbox.bind("<<ListboxSelect>>", self.on_conversation_select)
        conv_scroll.config(command=self.conv_listbox.yview)

        conv_btn_frame = ttk.Frame(left_frame)
        conv_btn_frame.pack(fill=tk.X, pady=5)
        ttk.Button(
            conv_btn_frame, text="New Conversation", command=self.new_conversation
        ).pack(fill=tk.X, pady=2)
        ttk.Button(
            conv_btn_frame, text="Delete Conversation", command=self.delete_conversation
        ).pack(fill=tk.X, pady=2)

        # Middle panel - Lines list
        middle_frame = ttk.Frame(main_frame, width=400)
        middle_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=(0, 5))

        ttk.Label(middle_frame, text="Dialogue Lines", font=("Arial", 12, "bold")).pack(
            pady=5
        )

        tree_frame = ttk.Frame(middle_frame)
        tree_frame.pack(fill=tk.BOTH, expand=True)

        tree_scroll = ttk.Scrollbar(tree_frame)
        tree_scroll.pack(side=tk.RIGHT, fill=tk.Y)

        self.lines_tree = ttk.Treeview(
            tree_frame,
            columns=("Line",),
            show="tree headings",
            yscrollcommand=tree_scroll.set,
            height=25,
        )
        self.lines_tree.heading("Line", text="Preview")
        self.lines_tree.column("#0", width=80)
        self.lines_tree.column("Line", width=300)
        self.lines_tree.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.lines_tree.bind("<<TreeviewSelect>>", self.on_line_select)
        tree_scroll.config(command=self.lines_tree.yview)

        line_btn_frame = ttk.Frame(middle_frame)
        line_btn_frame.pack(fill=tk.X, pady=5)
        ttk.Button(line_btn_frame, text="New Line", command=self.new_line).pack(
            side=tk.LEFT, padx=2
        )
        ttk.Button(line_btn_frame, text="Move Up", command=self.move_line_up).pack(
            side=tk.LEFT, padx=2
        )
        ttk.Button(line_btn_frame, text="Move Down", command=self.move_line_down).pack(
            side=tk.LEFT, padx=2
        )
        ttk.Button(line_btn_frame, text="Delete Line", command=self.delete_line).pack(
            side=tk.LEFT, padx=2
        )

        # Right panel - Line editor
        right_frame = ttk.Frame(main_frame)
        right_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        ttk.Label(right_frame, text="Line Editor", font=("Arial", 12, "bold")).pack(
            pady=5
        )

        canvas = tk.Canvas(right_frame)
        scrollbar = ttk.Scrollbar(right_frame, orient="vertical", command=canvas.yview)
        self.editor_frame = ttk.Frame(canvas)

        self.editor_frame.bind(
            "<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )
        canvas.create_window((0, 0), window=self.editor_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)

        canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        self.editor_vars = {}
        fields = [
            ("Name / ID", "name_id"),
            ("Portrait", "portrait"),
            ("Emotion", "emotion"),  # <-- Will become dropdown
            ("Action", "action"),  # <-- Will become dropdown
            ("Line1", "line1", 20),
            ("Line2", "line2", 20),
            ("Line3", "line3", 20),
            ("Color", "color"),  # <-- Will become dropdown
            ("Size", "size"),  # <-- Will become dropdown
            ("Speed", "speed"),  # <-- Will become dropdown
            ("Index", "index"),
            ("Anim", "anim"),
            ("Navigate", "navigate"),
            ("Branching Dialogue 1", "branching1"),
            ("Branching Dialogue 2", "branching2"),
            ("Bg Pointer", "bg_pointer"),
        ]

        # --- MODIFICATION START ---
        # Define which fields should be dropdowns based on loaded constants
        dropdown_fields = ["emotion", "action", "speed", "size", "color"]

        for i, field in enumerate(fields):
            label = field[0]
            var_name = field[1]
            max_len = field[2] if len(field) > 2 else None

            ttk.Label(
                self.editor_frame, text=label + ":", font=("Arial", 9, "bold")
            ).grid(row=i, column=0, sticky="w", padx=5, pady=3)

            var = tk.StringVar()
            self.editor_vars[var_name] = var

            if var_name == "branching1":
                widget = ttk.Combobox(self.editor_frame, textvariable=var, width=38)
                widget.grid(row=i, column=1, sticky="ew", padx=5, pady=3)
                self.branching1_combo = widget
            elif var_name == "branching2":
                widget = ttk.Combobox(self.editor_frame, textvariable=var, width=38)
                widget.grid(row=i, column=1, sticky="ew", padx=5, pady=3)
                self.branching2_combo = widget
            elif var_name in dropdown_fields:
                # Create a Combobox for our constant fields
                options = self.constant_options.get(var_name, [""])
                widget = ttk.Combobox(
                    self.editor_frame, textvariable=var, values=options, width=38
                )
                widget.grid(row=i, column=1, sticky="ew", padx=5, pady=3)
            else:
                # Default to Entry for all other fields
                entry = ttk.Entry(self.editor_frame, textvariable=var, width=40)
                entry.grid(row=i, column=1, sticky="ew", padx=5, pady=3)

                if max_len:
                    char_label = ttk.Label(
                        self.editor_frame, text=f"0/{max_len}", foreground="gray"
                    )
                    char_label.grid(row=i, column=2, padx=5)
                    var.trace_add(
                        "write",
                        lambda *args, v=var, lbl=char_label, ml=max_len: self.update_char_count(
                            v, lbl, ml
                        ),
                    )

            var.trace_add("write", lambda *args: self.mark_dialogue_modified())
        # --- MODIFICATION END ---

        self.editor_frame.columnconfigure(1, weight=1)

        ttk.Button(
            self.editor_frame, text="Apply Changes", command=self.apply_changes
        ).grid(row=len(fields), column=0, columnspan=3, pady=10)

        self.current_conv_index = None
        self.current_line_index = None

    def refresh(self):
        """Refreshes the dialogue tab UI. Renamed from refresh_dialogue_tab."""
        self.refresh_conversation_list()
        self.lines_tree.delete(*self.lines_tree.get_children())
        self.clear_editor()

    def update_char_count(self, var, label, max_len):
        text = var.get()
        length = len(text)
        label.config(text=f"{length}/{max_len}")
        if length > max_len:
            label.config(foreground="red")
        else:
            label.config(foreground="gray")

    def update_branching_combos(self):
        """Updates the values in the branching dialogue comboboxes."""
        conv_names = [conv["name"] for conv in self.dialogue_data]
        options = [""] + ["&" + name for name in conv_names]

        if self.branching1_combo:
            self.branching1_combo["values"] = options
        if self.branching2_combo:
            self.branching2_combo["values"] = options

    def mark_dialogue_modified(self):
        """Notifies the main app that data has changed."""
        self.app.mark_dialogue_modified()

    def refresh_conversation_list(self):
        self.conv_listbox.delete(0, tk.END)
        for conv in self.dialogue_data:
            self.conv_listbox.insert(tk.END, conv["name"])
        # Update comboboxes whenever the conversation list changes
        self.update_branching_combos()

    def on_conversation_select(self, event):
        selection = self.conv_listbox.curselection()
        if not selection:
            return

        self.current_conv_index = selection[0]
        self.refresh_lines_list()
        self.clear_editor()

    def refresh_lines_list(self):
        self.lines_tree.delete(*self.lines_tree.get_children())

        if self.current_conv_index is None or self.current_conv_index >= len(
            self.dialogue_data
        ):
            return

        conv = self.dialogue_data[self.current_conv_index]
        for i, line in enumerate(conv["lines"]):
            preview = " ".join([line["line1"], line["line2"], line["line3"]]).strip()
            if not preview:
                preview = f"[{line['action'] or line['emotion'] or 'Empty line'}]"

            display = f"Line {i+1}"
            if line["name_id"]:
                display += f" ({line['name_id']})"

            self.lines_tree.insert(
                "", tk.END, iid=str(i), text=display, values=(preview,)
            )

    def on_line_select(self, event):
        selection = self.lines_tree.selection()
        if not selection:
            return

        # Check if event is None (manual call)
        if event is not None:
            self.current_line_index = int(selection[0])
        elif selection:
            self.current_line_index = int(selection[0])
        else:
            self.current_line_index = None

        self.load_line_to_editor()

    def load_line_to_editor(self):
        if self.current_conv_index is None or self.current_line_index is None:
            return

        try:
            line = self.dialogue_data[self.current_conv_index]["lines"][
                self.current_line_index
            ]
            for key, var in self.editor_vars.items():
                var.set(line.get(key, ""))
        except IndexError:
            self.clear_editor()

    def clear_editor(self):
        for var in self.editor_vars.values():
            var.set("")
        self.current_line_index = None

    def apply_changes(self):
        if self.current_conv_index is None or self.current_line_index is None:
            messagebox.showwarning("No Selection", "Please select a line to edit.")
            return

        for field in ["line1", "line2", "line3"]:
            if len(self.editor_vars[field].get()) > 20:
                messagebox.showerror(
                    "Validation Error", f"{field.title()} exceeds 20 characters!"
                )
                return

        try:
            line = self.dialogue_data[self.current_conv_index]["lines"][
                self.current_line_index
            ]
            for key, var in self.editor_vars.items():
                line[key] = var.get()

            self.refresh_lines_list()
            self.mark_dialogue_modified()
            self.lines_tree.selection_set(str(self.current_line_index))
            messagebox.showinfo("Success", "Changes applied!")

        except IndexError:
            messagebox.showerror(
                "Error", "Could not apply changes. Line index out of range."
            )

    def new_conversation(self):
        name = simpledialog.askstring(
            "New Conversation", "Enter conversation name/ID:", parent=self.root
        )
        if name:
            self.dialogue_data.append({"name": name, "lines": []})
            self.refresh_conversation_list()
            self.conv_listbox.selection_clear(0, tk.END)
            self.conv_listbox.selection_set(tk.END)
            self.conv_listbox.event_generate("<<ListboxSelect>>")
            self.mark_dialogue_modified()

    def delete_conversation(self):
        if self.current_conv_index is None:
            return

        if messagebox.askyesno("Confirm Delete", "Delete this conversation?"):
            del self.dialogue_data[self.current_conv_index]
            self.refresh_conversation_list()
            self.clear_editor()
            self.lines_tree.delete(*self.lines_tree.get_children())
            self.current_conv_index = None
            self.mark_dialogue_modified()

    def new_line(self):
        if self.current_conv_index is None:
            messagebox.showwarning(
                "No Conversation", "Please select a conversation first."
            )
            return

        new_line = {key: "" for key in self.editor_vars.keys()}
        self.dialogue_data[self.current_conv_index]["lines"].append(new_line)
        self.refresh_lines_list()

        new_index = len(self.dialogue_data[self.current_conv_index]["lines"]) - 1
        self.lines_tree.selection_set(str(new_index))
        # Pass None to on_line_select to simulate the event
        self.on_line_select(None)
        self.mark_dialogue_modified()

    def delete_line(self):
        if self.current_conv_index is None or self.current_line_index is None:
            return

        if messagebox.askyesno("Confirm Delete", "Delete this line?"):
            del self.dialogue_data[self.current_conv_index]["lines"][
                self.current_line_index
            ]
            self.refresh_lines_list()
            self.clear_editor()
            self.mark_dialogue_modified()

    def move_line_up(self):
        if self.current_line_index is None or self.current_line_index == 0:
            return

        lines = self.dialogue_data[self.current_conv_index]["lines"]
        lines[self.current_line_index], lines[self.current_line_index - 1] = (
            lines[self.current_line_index - 1],
            lines[self.current_line_index],
        )

        new_index = self.current_line_index - 1
        self.refresh_lines_list()
        self.lines_tree.selection_set(str(new_index))
        self.on_line_select(None)
        self.mark_dialogue_modified()

    def move_line_down(self):
        if self.current_line_index is None:
            return

        lines = self.dialogue_data[self.current_conv_index]["lines"]
        if self.current_line_index >= len(lines) - 1:
            return

        lines[self.current_line_index], lines[self.current_line_index + 1] = (
            lines[self.current_line_index + 1],
            lines[self.current_line_index],
        )

        new_index = self.current_line_index + 1
        self.refresh_lines_list()
        self.lines_tree.selection_set(str(new_index))
        self.on_line_select(None)
        self.mark_dialogue_modified()
