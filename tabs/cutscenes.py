# tab_cutscenes.py

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog


class CutscenesTab:
    def __init__(self, notebook, app):
        self.app = app
        self.root = app.root
        self.data = app.get_json_data()

        self.frame = ttk.Frame(notebook)
        notebook.add(self.frame, text="Cutscenes")

        self.create_widgets()
        self.refresh()

    def create_widgets(self):
        ttk.Label(self.frame, text="Cutscenes:", font=("Arial", 10, "bold")).pack(
            pady=5
        )

        self.cutscenes_listbox = tk.Listbox(self.frame, height=20)
        self.cutscenes_listbox.pack(fill="both", expand=True, padx=5)

        btn_frame = ttk.Frame(self.frame)
        btn_frame.pack(fill="x", padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Cutscene", command=self.add_cutscene).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Edit Cutscene", command=self.edit_cutscene).pack(
            side="left", padx=2
        )
        ttk.Button(
            btn_frame, text="Delete Cutscene", command=self.delete_cutscene
        ).pack(side="left", padx=2)

    def refresh(self):
        """Renamed from refresh_cutscenes"""
        self.cutscenes_listbox.delete(0, tk.END)
        for cutscene in self.data.get("cutscenes", {}).keys():
            props = self.data["cutscenes"][cutscene]
            details = []
            if "type" in props:
                details.append(f"type: {props['type']}")
            if "music" in props:
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
        cutscene_name = cutscene_display.split(" (")[0]
        self.edit_cutscene_dialog(cutscene_name)

    def edit_cutscene_dialog(self, cutscene_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Cutscene" if cutscene_name else "Add Cutscene")
        dialog.geometry("400x300")

        ttk.Label(dialog, text="Cutscene Name:").grid(
            row=0, column=0, sticky="w", padx=5, pady=5
        )
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Conversation:").grid(
            row=1, column=0, sticky="w", padx=5, pady=5
        )
        conv_entry = ttk.Entry(dialog, width=30)
        conv_entry.grid(row=1, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Music:").grid(
            row=2, column=0, sticky="w", padx=5, pady=5
        )
        music_entry = ttk.Entry(dialog, width=30)
        music_entry.grid(row=2, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Type:").grid(
            row=3, column=0, sticky="w", padx=5, pady=5
        )
        type_entry = ttk.Entry(dialog, width=30)
        type_entry.grid(row=3, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Background:").grid(
            row=4, column=0, sticky="w", padx=5, pady=5
        )
        bg_entry = ttk.Entry(dialog, width=30)
        bg_entry.grid(row=4, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="SFX:").grid(row=5, column=0, sticky="w", padx=5, pady=5)
        sfx_entry = ttk.Entry(dialog, width=30)
        sfx_entry.grid(row=5, column=1, padx=5, pady=5)

        if cutscene_name:
            cutscene_data = self.data["cutscenes"][cutscene_name]
            name_entry.insert(0, cutscene_name)
            if "conversation" in cutscene_data:
                conv_entry.insert(0, cutscene_data["conversation"])
            if "music" in cutscene_data:
                music_entry.insert(0, str(cutscene_data["music"]))
            if "type" in cutscene_data:
                type_entry.insert(0, cutscene_data["type"])
            if "bg" in cutscene_data:
                bg_entry.insert(0, cutscene_data["bg"])
            if "sfx" in cutscene_data:
                sfx_entry.insert(0, cutscene_data["sfx"])

        def save_cutscene():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Cutscene name cannot be empty!")
                return

            if cutscene_name and cutscene_name != new_name:
                del self.data["cutscenes"][cutscene_name]

            cutscene_data = {}
            if conv_entry.get().strip():
                cutscene_data["conversation"] = conv_entry.get().strip()
            if music_entry.get().strip():
                music_val = music_entry.get().strip()
                if music_val.lower() == "false":
                    cutscene_data["music"] = False
                else:
                    cutscene_data["music"] = music_val
            if type_entry.get().strip():
                cutscene_data["type"] = type_entry.get().strip()
            if bg_entry.get().strip():
                cutscene_data["bg"] = bg_entry.get().strip()
            if sfx_entry.get().strip():
                cutscene_data["sfx"] = sfx_entry.get().strip()

            self.data["cutscenes"][new_name] = cutscene_data
            self.refresh()
            dialog.destroy()

        ttk.Button(dialog, text="Save", command=save_cutscene).grid(
            row=6, column=0, columnspan=2, pady=20
        )

    def delete_cutscene(self):
        selection = self.cutscenes_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select a cutscene to delete!")
            return

        cutscene_display = self.cutscenes_listbox.get(selection[0])
        cutscene_name = cutscene_display.split(" (")[0]

        if messagebox.askyesno("Confirm", f"Delete cutscene '{cutscene_name}'?"):
            del self.data["cutscenes"][cutscene_name]
            self.refresh()
