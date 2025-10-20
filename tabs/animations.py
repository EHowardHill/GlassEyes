# tab_animations.py

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog


class AnimationsTab:
    def __init__(self, notebook, app):
        self.app = app
        self.root = app.root
        self.data = app.get_json_data()

        self.frame = ttk.Frame(notebook)
        notebook.add(self.frame, text="Animations")

        self.create_widgets()
        self.refresh()

    def create_widgets(self):
        # Left panel - entity list
        left_frame = ttk.Frame(self.frame)
        left_frame.pack(side="left", fill="both", expand=True, padx=5, pady=5)

        ttk.Label(left_frame, text="Entities:", font=("Arial", 10, "bold")).pack()

        self.anim_entity_listbox = tk.Listbox(left_frame, height=15)
        self.anim_entity_listbox.pack(fill="both", expand=True)
        self.anim_entity_listbox.bind("<<ListboxSelect>>", self.on_entity_select)

        btn_frame = ttk.Frame(left_frame)
        btn_frame.pack(fill="x", pady=5)
        ttk.Button(
            btn_frame, text="Add Entity", command=self.add_animation_entity
        ).pack(side="left", padx=2)
        ttk.Button(
            btn_frame, text="Delete Entity", command=self.delete_animation_entity
        ).pack(side="left", padx=2)

        # Right panel - animation list
        right_frame = ttk.Frame(self.frame)
        right_frame.pack(side="right", fill="both", expand=True, padx=5, pady=5)

        ttk.Label(right_frame, text="Animations:", font=("Arial", 10, "bold")).pack()

        self.anim_listbox = tk.Listbox(right_frame, height=15)
        self.anim_listbox.pack(fill="both", expand=True)

        btn_frame2 = ttk.Frame(right_frame)
        btn_frame2.pack(fill="x", pady=5)
        ttk.Button(btn_frame2, text="Add Animation", command=self.add_animation).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame2, text="Edit Animation", command=self.edit_animation).pack(
            side="left", padx=2
        )
        ttk.Button(
            btn_frame2, text="Delete Animation", command=self.delete_animation
        ).pack(side="left", padx=2)

    def refresh(self):
        """Renamed from refresh_animations"""
        self.anim_entity_listbox.delete(0, tk.END)
        for entity in self.data.get("animations", {}).keys():
            self.anim_entity_listbox.insert(tk.END, entity)

        # Clear the animation list as well
        if hasattr(self, "anim_listbox"):
            self.anim_listbox.delete(0, tk.END)

    def on_entity_select(self, event):
        selection = self.anim_entity_listbox.curselection()
        if selection:
            entity = self.anim_entity_listbox.get(selection[0])
            self.anim_listbox.delete(0, tk.END)
            for anim_name in self.data["animations"][entity].keys():
                self.anim_listbox.insert(tk.END, anim_name)

    def add_animation_entity(self):
        entity = simpledialog.askstring(
            "Add Entity", "Enter entity name:", parent=self.root
        )
        if entity:
            if entity in self.data["animations"]:
                messagebox.showwarning("Warning", "Entity already exists!")
            else:
                self.data["animations"][entity] = {}
                self.refresh()

    def delete_animation_entity(self):
        selection = self.anim_entity_listbox.curselection()
        if selection:
            entity = self.anim_entity_listbox.get(selection[0])
            if messagebox.askyesno(
                "Confirm", f"Delete entity '{entity}' and all its animations?"
            ):
                del self.data["animations"][entity]
                self.refresh()

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

        ttk.Label(dialog, text="Animation Name:").grid(
            row=0, column=0, sticky="w", padx=5, pady=5
        )
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Frames (comma-separated):").grid(
            row=1, column=0, sticky="w", padx=5, pady=5
        )
        frames_entry = ttk.Entry(dialog, width=30)
        frames_entry.grid(row=1, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Speed:").grid(
            row=2, column=0, sticky="w", padx=5, pady=5
        )
        speed_entry = ttk.Entry(dialog, width=30)
        speed_entry.grid(row=2, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Loop:").grid(
            row=3, column=0, sticky="w", padx=5, pady=5
        )
        loop_var = tk.BooleanVar()
        loop_check = ttk.Checkbutton(dialog, variable=loop_var)
        loop_check.grid(row=3, column=1, sticky="w", padx=5, pady=5)

        if anim_name:
            anim_data = self.data["animations"][entity][anim_name]
            name_entry.insert(0, anim_name)
            frames_entry.insert(0, ",".join(map(str, anim_data["frames"])))
            speed_entry.insert(0, str(anim_data["speed"]))
            loop_var.set(anim_data["loop"])

        def save_animation():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Animation name cannot be empty!")
                return

            try:
                frames = [int(x.strip()) for x in frames_entry.get().split(",")]
                speed = int(speed_entry.get())
            except ValueError:
                messagebox.showerror("Error", "Invalid frames or speed value!")
                return

            if anim_name and anim_name != new_name:
                del self.data["animations"][entity][anim_name]

            self.data["animations"][entity][new_name] = {
                "frames": frames,
                "speed": speed,
                "loop": loop_var.get(),
            }

            self.on_entity_select(None)
            dialog.destroy()

        ttk.Button(dialog, text="Save", command=save_animation).grid(
            row=4, column=0, columnspan=2, pady=20
        )

    def delete_animation(self):
        entity_sel = self.anim_entity_listbox.curselection()
        anim_sel = self.anim_listbox.curselection()

        if not entity_sel or not anim_sel:
            messagebox.showwarning("Warning", "Please select an animation to delete!")
            return

        entity = self.anim_entity_listbox.get(entity_sel[0])
        anim_name = self.anim_listbox.get(anim_sel[0])

        if messagebox.askyesno("Confirm", f"Delete animation '{anim_name}'?"):
            del self.data["animations"][entity][anim_name]
            self.on_entity_select(None)
