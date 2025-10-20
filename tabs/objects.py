# tab_objects.py

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog


class ObjectsTab:
    def __init__(self, notebook, app):
        self.app = app
        self.root = app.root
        self.data = app.get_json_data()

        self.frame = ttk.Frame(notebook)
        notebook.add(self.frame, text="Objects")

        self.create_widgets()
        self.refresh()

    def create_widgets(self):
        ttk.Label(self.frame, text="Objects:", font=("Arial", 10, "bold")).pack(pady=5)

        self.objects_listbox = tk.Listbox(self.frame, height=20)
        self.objects_listbox.pack(fill="both", expand=True, padx=5)

        btn_frame = ttk.Frame(self.frame)
        btn_frame.pack(fill="x", padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Object", command=self.add_object).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Edit Object", command=self.edit_object).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Delete Object", command=self.delete_object).pack(
            side="left", padx=2
        )

    def refresh(self):
        """Renamed from refresh_objects"""
        self.objects_listbox.delete(0, tk.END)
        object_keys = list(self.data.get("objects", {}).keys())

        for i, obj in enumerate(object_keys):
            object_id = i + 2
            props = self.data["objects"][obj]
            details = []
            if "follow" in props:
                details.append(f"follow: {props['follow']}")
            if "idle_animation" in props:
                details.append(f"idle: {props['idle_animation']}")
            if "is_pressed" in props:
                details.append(f"pressed: {props['is_pressed']}")

            details_str = f" ({', '.join(details)})" if details else ""
            display = f"ID {object_id}: {obj}{details_str}"
            self.objects_listbox.insert(tk.END, display)

    def add_object(self):
        self.edit_object_dialog(None)

    def edit_object(self):
        selection = self.objects_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an object to edit!")
            return

        obj_display = self.objects_listbox.get(selection[0])
        obj_name = obj_display.split(": ")[1].split(" (")[0]
        self.edit_object_dialog(obj_name)

    def edit_object_dialog(self, obj_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Object" if obj_name else "Add Object")
        dialog.geometry("400x250")

        ttk.Label(dialog, text="Object Name:").grid(
            row=0, column=0, sticky="w", padx=5, pady=5
        )
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Follow:").grid(
            row=1, column=0, sticky="w", padx=5, pady=5
        )
        follow_entry = ttk.Entry(dialog, width=30)
        follow_entry.grid(row=1, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Idle Animation:").grid(
            row=2, column=0, sticky="w", padx=5, pady=5
        )
        idle_entry = ttk.Entry(dialog, width=30)
        idle_entry.grid(row=2, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Is Pressed:").grid(
            row=3, column=0, sticky="w", padx=5, pady=5
        )
        pressed_var = tk.BooleanVar()
        pressed_check = ttk.Checkbutton(dialog, variable=pressed_var)
        pressed_check.grid(row=3, column=1, sticky="w", padx=5, pady=5)

        if obj_name:
            obj_data = self.data["objects"][obj_name]
            name_entry.insert(0, obj_name)
            if "follow" in obj_data:
                follow_entry.insert(0, obj_data["follow"])
            if "idle_animation" in obj_data:
                idle_entry.insert(0, obj_data["idle_animation"])
            if "is_pressed" in obj_data:
                pressed_var.set(obj_data["is_pressed"])

        def save_object():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Object name cannot be empty!")
                return

            if obj_name and obj_name != new_name:
                new_objects = {}
                for key, value in self.data["objects"].items():
                    if key == obj_name:
                        new_objects[new_name] = value
                    else:
                        new_objects[key] = value
                self.data["objects"] = new_objects

            obj_data = {}
            if follow_entry.get().strip():
                obj_data["follow"] = follow_entry.get().strip()
            if idle_entry.get().strip():
                obj_data["idle_animation"] = idle_entry.get().strip()
            if pressed_var.get():
                obj_data["is_pressed"] = True

            self.data["objects"][new_name] = obj_data
            self.refresh()
            dialog.destroy()

        ttk.Button(dialog, text="Save", command=save_object).grid(
            row=4, column=0, columnspan=2, pady=20
        )

    def delete_object(self):
        selection = self.objects_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an object to delete!")
            return

        obj_display = self.objects_listbox.get(selection[0])
        obj_name = obj_display.split(": ")[1].split(" (")[0]

        if messagebox.askyesno("Confirm", f"Delete object '{obj_name}'?"):
            del self.data["objects"][obj_name]
            self.refresh()
