# actions.py

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog


class ActionsTab:
    def __init__(self, notebook, app):
        self.app = app
        self.root = app.root
        self.data = app.get_json_data()

        self.frame = ttk.Frame(notebook)
        notebook.add(self.frame, text="Actions")

        self.create_widgets()
        self.refresh()

    def create_widgets(self):
        top_frame = ttk.Frame(self.frame)
        top_frame.pack(fill="x", padx=5, pady=5)

        ttk.Label(top_frame, text="Action Type:", font=("Arial", 10, "bold")).pack(
            side="left", padx=5
        )

        self.action_type_var = tk.StringVar(value="interactable")
        ttk.Radiobutton(
            top_frame,
            text="Interactable",
            variable=self.action_type_var,
            value="interactable",
            command=self.refresh,
        ).pack(side="left", padx=5)
        ttk.Radiobutton(
            top_frame,
            text="Automatic",
            variable=self.action_type_var,
            value="automatic",
            command=self.refresh,
        ).pack(side="left", padx=5)

        ttk.Label(self.frame, text="Actions:", font=("Arial", 10, "bold")).pack(pady=5)

        self.actions_listbox = tk.Listbox(self.frame, height=20)
        self.actions_listbox.pack(fill="both", expand=True, padx=5)

        btn_frame = ttk.Frame(self.frame)
        btn_frame.pack(fill="x", padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Action", command=self.add_action).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Edit Action", command=self.edit_action).pack(
            side="left", padx=2
        )
        ttk.Button(
            btn_frame, text="Duplicate Action", command=self.duplicate_action
        ).pack(side="left", padx=2)
        ttk.Button(btn_frame, text="Delete Action", command=self.delete_action).pack(
            side="left", padx=2
        )

    def refresh(self):
        """Renamed from refresh_actions"""
        self.actions_listbox.delete(0, tk.END)

        if "actions" not in self.data:
            self.data["actions"] = {"interactable": {}, "automatic": {}}

        action_type = self.action_type_var.get()
        actions = self.data["actions"].get(action_type, {})

        for action_id in sorted(actions.keys(), key=lambda x: int(x)):
            props = actions[action_id]
            details = []

            if "auto" in props:
                details.append(f"auto: {props['auto']}")
            if "sequence" in props:
                details.append(f"seq: {len(props['sequence'])} items")
            if "stage" in props:
                details.append(f"stage: {props['stage']}")
            if "music" in props:
                details.append(f"music: {props['music']}")
            if "new_map" in props:
                details.append(f"new_map: {props['new_map'].get('map', 'N/A')}")

            display = f"ID {action_id}" + (
                f" ({', '.join(details)})" if details else ""
            )
            self.actions_listbox.insert(tk.END, display)

    def add_action(self):
        self.edit_action_dialog(None)

    def edit_action(self):
        selection = self.actions_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an action to edit!")
            return

        action_display = self.actions_listbox.get(selection[0])
        action_id = action_display.split(" (")[0].replace("ID ", "")
        self.edit_action_dialog(action_id)

    def duplicate_action(self):
        selection = self.actions_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an action to duplicate!")
            return

        action_display = self.actions_listbox.get(selection[0])
        action_id = action_display.split(" (")[0].replace("ID ", "")
        action_type = self.action_type_var.get()

        # Get the action data to duplicate
        original_action = self.data["actions"][action_type][action_id]

        # Find the next available ID
        max_id = 0
        for atype in ["interactable", "automatic"]:
            if atype in self.data["actions"]:
                for existing_id in self.data["actions"][atype].keys():
                    try:
                        id_num = int(existing_id)
                        if id_num > max_id:
                            max_id = id_num
                    except ValueError:
                        pass

        new_id = str(max_id + 1)

        # Create a deep copy of the action data
        import copy

        duplicated_action = copy.deepcopy(original_action)

        # Add the duplicated action with the new ID
        self.data["actions"][action_type][new_id] = duplicated_action

        # Refresh the display
        self.refresh()

        # Show success message
        messagebox.showinfo("Success", f"Action duplicated with new ID: {new_id}")

    def edit_action_dialog(self, action_id):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Action" if action_id else "Add Action")
        dialog.geometry("600x650")

        canvas = tk.Canvas(dialog)
        scrollbar = ttk.Scrollbar(dialog, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)

        scrollable_frame.bind(
            "<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )

        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)

        row = 0

        ttk.Label(scrollable_frame, text="Action ID:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        id_entry = ttk.Entry(scrollable_frame, width=40)
        id_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="Sequence (comma-separated):").grid(
            row=row, column=0, sticky="nw", padx=5, pady=5
        )
        sequence_entry = ttk.Entry(scrollable_frame, width=40)
        sequence_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="Auto:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        auto_entry = ttk.Entry(scrollable_frame, width=40)
        auto_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="Stage:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        stage_entry = ttk.Entry(scrollable_frame, width=40)
        stage_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="Music:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        music_entry = ttk.Entry(scrollable_frame, width=40)
        music_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Separator(scrollable_frame, orient="horizontal").grid(
            row=row, column=0, columnspan=2, sticky="ew", pady=10
        )
        row += 1

        ttk.Label(
            scrollable_frame, text="New Map Properties:", font=("Arial", 9, "bold")
        ).grid(row=row, column=0, columnspan=2, sticky="w", padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="Map:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        map_entry = ttk.Entry(scrollable_frame, width=40)
        map_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="BG Track:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        bg_track_entry = ttk.Entry(scrollable_frame, width=40)
        bg_track_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="BG:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        bg_entry = ttk.Entry(scrollable_frame, width=40)
        bg_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Separator(scrollable_frame, orient="horizontal").grid(
            row=row, column=0, columnspan=2, sticky="ew", pady=10
        )
        row += 1

        ttk.Label(
            scrollable_frame, text="Entity Positions:", font=("Arial", 9, "bold")
        ).grid(row=row, column=0, columnspan=2, sticky="w", padx=5, pady=5)
        row += 1

        positions_frame = ttk.Frame(scrollable_frame)
        positions_frame.grid(
            row=row, column=0, columnspan=2, padx=5, pady=5, sticky="ew"
        )

        positions_listbox = tk.Listbox(positions_frame, height=6, width=50)
        positions_listbox.pack(side="left", fill="both", expand=True)

        positions_scroll = ttk.Scrollbar(
            positions_frame, orient="vertical", command=positions_listbox.yview
        )
        positions_scroll.pack(side="right", fill="y")
        positions_listbox.config(yscrollcommand=positions_scroll.set)

        positions_data = {}

        def refresh_positions_list():
            positions_listbox.delete(0, tk.END)
            for entity, coords in sorted(positions_data.items()):
                positions_listbox.insert(
                    tk.END, f"{entity}: [{coords[0]}, {coords[1]}]"
                )

        def add_position():
            pos_dialog = tk.Toplevel(dialog)
            pos_dialog.title("Add Position")
            pos_dialog.geometry("300x150")

            ttk.Label(pos_dialog, text="Entity Name:").grid(
                row=0, column=0, sticky="w", padx=5, pady=5
            )
            entity_entry = ttk.Entry(pos_dialog, width=20)
            entity_entry.grid(row=0, column=1, padx=5, pady=5)

            ttk.Label(pos_dialog, text="X Coordinate:").grid(
                row=1, column=0, sticky="w", padx=5, pady=5
            )
            x_entry = ttk.Entry(pos_dialog, width=20)
            x_entry.grid(row=1, column=1, padx=5, pady=5)

            ttk.Label(pos_dialog, text="Y Coordinate:").grid(
                row=2, column=0, sticky="w", padx=5, pady=5
            )
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

            ttk.Button(pos_dialog, text="Save", command=save_position).grid(
                row=3, column=0, columnspan=2, pady=10
            )

        def edit_position():
            selection = positions_listbox.curselection()
            if not selection:
                messagebox.showwarning("Warning", "Please select a position to edit!")
                return

            selected_text = positions_listbox.get(selection[0])
            entity = selected_text.split(":")[0].strip()
            coords = positions_data[entity]

            pos_dialog = tk.Toplevel(dialog)
            pos_dialog.title("Edit Position")
            pos_dialog.geometry("300x150")

            ttk.Label(pos_dialog, text="Entity Name:").grid(
                row=0, column=0, sticky="w", padx=5, pady=5
            )
            entity_entry = ttk.Entry(pos_dialog, width=20)
            entity_entry.grid(row=0, column=1, padx=5, pady=5)
            entity_entry.insert(0, entity)

            ttk.Label(pos_dialog, text="X Coordinate:").grid(
                row=1, column=0, sticky="w", padx=5, pady=5
            )
            x_entry = ttk.Entry(pos_dialog, width=20)
            x_entry.grid(row=1, column=1, padx=5, pady=5)
            x_entry.insert(0, str(coords[0]))

            ttk.Label(pos_dialog, text="Y Coordinate:").grid(
                row=2, column=0, sticky="w", padx=5, pady=5
            )
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

                if entity != new_entity:
                    del positions_data[entity]

                positions_data[new_entity] = [x, y]
                refresh_positions_list()
                pos_dialog.destroy()

            ttk.Button(pos_dialog, text="Save", command=save_position).grid(
                row=3, column=0, columnspan=2, pady=10
            )

        def delete_position():
            selection = positions_listbox.curselection()
            if not selection:
                messagebox.showwarning("Warning", "Please select a position to delete!")
                return

            selected_text = positions_listbox.get(selection[0])
            entity = selected_text.split(":")[0].strip()

            if messagebox.askyesno("Confirm", f"Delete position for '{entity}'?"):
                del positions_data[entity]
                refresh_positions_list()

        row += 1

        positions_btn_frame = ttk.Frame(scrollable_frame)
        positions_btn_frame.grid(row=row, column=0, columnspan=2, pady=5)
        ttk.Button(positions_btn_frame, text="Add Position", command=add_position).pack(
            side="left", padx=2
        )
        ttk.Button(
            positions_btn_frame, text="Edit Position", command=edit_position
        ).pack(side="left", padx=2)
        ttk.Button(
            positions_btn_frame, text="Delete Position", command=delete_position
        ).pack(side="left", padx=2)
        row += 1

        if action_id:
            action_type = self.action_type_var.get()
            action_data = self.data["actions"][action_type][action_id]

            id_entry.insert(0, action_id)
            id_entry.config(state="readonly")

            if "sequence" in action_data:
                sequence_entry.insert(0, ", ".join(action_data["sequence"]))
            if "auto" in action_data:
                auto_entry.insert(0, action_data["auto"])
            if "stage" in action_data:
                stage_entry.insert(0, action_data["stage"])
            if "music" in action_data:
                music_entry.insert(0, action_data["music"])

            if "new_map" in action_data:
                new_map = action_data["new_map"]
                if "map" in new_map:
                    map_entry.insert(0, new_map["map"])
                if "bg_track" in new_map:
                    bg_track_entry.insert(0, new_map["bg_track"])
                if "bg" in new_map:
                    bg_entry.insert(0, new_map["bg"])
                if "positions" in new_map:
                    positions_data.update(new_map["positions"])
                    refresh_positions_list()
        else:
            # Auto-populate ID with highest existing ID + 1
            max_id = 0
            for action_type in ["interactable", "automatic"]:
                if action_type in self.data["actions"]:
                    for existing_id in self.data["actions"][action_type].keys():
                        try:
                            id_num = int(existing_id)
                            if id_num > max_id:
                                max_id = id_num
                        except ValueError:
                            pass

            # Insert the next ID (highest + 1), but keep it editable
            id_entry.insert(0, str(max_id + 1))

        def save_action():
            new_id = id_entry.get().strip()
            if not new_id:
                messagebox.showwarning("Warning", "Action ID cannot be empty!")
                return

            try:
                int(new_id)
            except ValueError:
                messagebox.showerror("Error", "Action ID must be a number!")
                return

            action_type = self.action_type_var.get()

            if not action_id and new_id in self.data["actions"][action_type]:
                messagebox.showwarning(
                    "Warning", f"Action ID '{new_id}' already exists!"
                )
                return

            action_data = {}

            if sequence_entry.get().strip():
                action_data["sequence"] = [
                    s.strip() for s in sequence_entry.get().split(",")
                ]
            if auto_entry.get().strip():
                action_data["auto"] = auto_entry.get().strip()
            if stage_entry.get().strip():
                action_data["stage"] = stage_entry.get().strip()
            if music_entry.get().strip():
                action_data["music"] = music_entry.get().strip()

            new_map = {}
            if map_entry.get().strip():
                new_map["map"] = map_entry.get().strip()
            if bg_track_entry.get().strip():
                new_map["bg_track"] = bg_track_entry.get().strip()
            if bg_entry.get().strip():
                new_map["bg"] = bg_entry.get().strip()

            if positions_data:
                new_map["positions"] = positions_data.copy()

            if new_map:
                action_data["new_map"] = new_map

            if not action_data:
                messagebox.showwarning(
                    "Warning", "Action must have at least one property!"
                )
                return

            if action_id:
                del self.data["actions"][action_type][action_id]

            self.data["actions"][action_type][new_id] = action_data
            self.refresh()
            dialog.destroy()

        ttk.Button(scrollable_frame, text="Save", command=save_action).grid(
            row=row, column=0, columnspan=2, pady=20
        )

        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

    def delete_action(self):
        selection = self.actions_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an action to delete!")
            return

        action_display = self.actions_listbox.get(selection[0])
        action_id = action_display.split(" (")[0].replace("ID ", "")
        action_type = self.action_type_var.get()

        if messagebox.askyesno("Confirm", f"Delete action ID '{action_id}'?"):
            del self.data["actions"][action_type][action_id]
            self.refresh()
