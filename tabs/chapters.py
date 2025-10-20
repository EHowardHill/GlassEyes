# tab_chapters.py

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog


class ChaptersTab:
    def __init__(self, notebook, app):
        self.app = app
        self.root = app.root
        self.data = app.get_json_data()

        self.frame = ttk.Frame(notebook)
        notebook.add(self.frame, text="Chapters")

        self.create_widgets()
        self.refresh()

    def create_widgets(self):
        ttk.Label(self.frame, text="Chapters:", font=("Arial", 10, "bold")).pack(pady=5)

        self.chapters_listbox = tk.Listbox(self.frame, height=20)
        self.chapters_listbox.pack(fill="both", expand=True, padx=5)

        btn_frame = ttk.Frame(self.frame)
        btn_frame.pack(fill="x", padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Chapter", command=self.add_chapter).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Edit Chapter", command=self.edit_chapter).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Delete Chapter", command=self.delete_chapter).pack(
            side="left", padx=2
        )

    def refresh(self):
        """Renamed from refresh_chapters"""
        self.chapters_listbox.delete(0, tk.END)
        for chapter in self.data.get("chapters", {}).keys():
            props = self.data["chapters"][chapter]
            details = []
            if "map" in props:
                details.append(f"map: {props['map']}")
            if "cutscenes" in props:
                details.append(f"cutscenes: {len(props['cutscenes'])}")

            display = f"{chapter}" + (f" ({', '.join(details)})" if details else "")
            self.chapters_listbox.insert(tk.END, display)

    def add_chapter(self):
        self.edit_chapter_dialog(None)

    def edit_chapter(self):
        selection = self.chapters_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select a chapter to edit!")
            return

        chapter_display = self.chapters_listbox.get(selection[0])
        chapter_name = chapter_display.split(" (")[0]
        self.edit_chapter_dialog(chapter_name)

    def edit_chapter_dialog(self, chapter_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Chapter" if chapter_name else "Add Chapter")
        dialog.geometry("600x700")

        canvas = tk.Canvas(dialog)
        scrollbar = ttk.Scrollbar(dialog, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)

        scrollable_frame.bind(
            "<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )

        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)

        row = 0

        ttk.Label(scrollable_frame, text="Chapter Name:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        name_entry = ttk.Entry(scrollable_frame, width=40)
        name_entry.grid(row=row, column=1, padx=5, pady=5)
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

        ttk.Label(scrollable_frame, text="SFX:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        sfx_entry = ttk.Entry(scrollable_frame, width=40)
        sfx_entry.grid(row=row, column=1, padx=5, pady=5)
        row += 1

        ttk.Label(scrollable_frame, text="Reset Health:").grid(
            row=row, column=0, sticky="w", padx=5, pady=5
        )
        reset_health_var = tk.BooleanVar()
        reset_health_check = ttk.Checkbutton(
            scrollable_frame, variable=reset_health_var
        )
        reset_health_check.grid(row=row, column=1, sticky="w", padx=5, pady=5)
        row += 1

        ttk.Separator(scrollable_frame, orient="horizontal").grid(
            row=row, column=0, columnspan=2, sticky="ew", pady=10
        )
        row += 1

        ttk.Label(scrollable_frame, text="Cutscenes:", font=("Arial", 9, "bold")).grid(
            row=row, column=0, columnspan=2, sticky="w", padx=5, pady=5
        )
        row += 1

        cutscenes_frame = ttk.Frame(scrollable_frame)
        cutscenes_frame.grid(
            row=row, column=0, columnspan=2, padx=5, pady=5, sticky="ew"
        )

        cutscenes_listbox = tk.Listbox(cutscenes_frame, height=6, width=50)
        cutscenes_listbox.pack(side="left", fill="both", expand=True)

        cutscenes_scroll = ttk.Scrollbar(
            cutscenes_frame, orient="vertical", command=cutscenes_listbox.yview
        )
        cutscenes_scroll.pack(side="right", fill="y")
        cutscenes_listbox.config(yscrollcommand=cutscenes_scroll.set)

        cutscenes_data = []

        def refresh_cutscenes_list():
            cutscenes_listbox.delete(0, tk.END)
            for cutscene in cutscenes_data:
                cutscenes_listbox.insert(tk.END, cutscene)

        def add_cutscene_to_list():
            cs_dialog = tk.Toplevel(dialog)
            cs_dialog.title("Add Cutscene")
            cs_dialog.geometry("300x100")

            ttk.Label(cs_dialog, text="Select Cutscene:").grid(
                row=0, column=0, sticky="w", padx=5, pady=5
            )

            cutscene_combo = ttk.Combobox(cs_dialog, width=25, state="readonly")
            cutscene_combo["values"] = list(self.data.get("cutscenes", {}).keys())
            cutscene_combo.grid(row=0, column=1, padx=5, pady=5)

            def save_cutscene():
                cutscene = cutscene_combo.get().strip()
                if not cutscene:
                    messagebox.showwarning("Warning", "Please select a cutscene!")
                    return

                cutscenes_data.append(cutscene)
                refresh_cutscenes_list()
                cs_dialog.destroy()

            ttk.Button(cs_dialog, text="Add", command=save_cutscene).grid(
                row=1, column=0, columnspan=2, pady=10
            )

        def edit_cutscene_in_list():
            selection = cutscenes_listbox.curselection()
            if not selection:
                messagebox.showwarning("Warning", "Please select a cutscene to edit!")
                return

            idx = selection[0]
            current_cutscene = cutscenes_data[idx]

            cs_dialog = tk.Toplevel(dialog)
            cs_dialog.title("Edit Cutscene")
            cs_dialog.geometry("300x100")

            ttk.Label(cs_dialog, text="Select Cutscene:").grid(
                row=0, column=0, sticky="w", padx=5, pady=5
            )

            cutscene_combo = ttk.Combobox(cs_dialog, width=25, state="readonly")
            cutscene_combo["values"] = list(self.data.get("cutscenes", {}).keys())
            cutscene_combo.set(current_cutscene)
            cutscene_combo.grid(row=0, column=1, padx=5, pady=5)

            def save_cutscene():
                cutscene = cutscene_combo.get().strip()
                if not cutscene:
                    messagebox.showwarning("Warning", "Please select a cutscene!")
                    return

                cutscenes_data[idx] = cutscene
                refresh_cutscenes_list()
                cs_dialog.destroy()

            ttk.Button(cs_dialog, text="Save", command=save_cutscene).grid(
                row=1, column=0, columnspan=2, pady=10
            )

        def delete_cutscene_from_list():
            selection = cutscenes_listbox.curselection()
            if not selection:
                messagebox.showwarning("Warning", "Please select a cutscene to delete!")
                return

            idx = selection[0]
            if messagebox.askyesno(
                "Confirm", f"Delete cutscene '{cutscenes_data[idx]}'?"
            ):
                del cutscenes_data[idx]
                refresh_cutscenes_list()

        row += 1

        cutscenes_btn_frame = ttk.Frame(scrollable_frame)
        cutscenes_btn_frame.grid(row=row, column=0, columnspan=2, pady=5)
        ttk.Button(
            cutscenes_btn_frame, text="Add Cutscene", command=add_cutscene_to_list
        ).pack(side="left", padx=2)
        ttk.Button(
            cutscenes_btn_frame, text="Edit Cutscene", command=edit_cutscene_in_list
        ).pack(side="left", padx=2)
        ttk.Button(
            cutscenes_btn_frame,
            text="Delete Cutscene",
            command=delete_cutscene_from_list,
        ).pack(side="left", padx=2)
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

        if chapter_name:
            chapter_data = self.data["chapters"][chapter_name]

            name_entry.insert(0, chapter_name)
            name_entry.config(state="readonly")

            if "map" in chapter_data:
                map_entry.insert(0, chapter_data["map"])
            if "bg_track" in chapter_data:
                bg_track_entry.insert(0, chapter_data["bg_track"])
            if "bg" in chapter_data:
                bg_entry.insert(0, chapter_data["bg"])
            if "sfx" in chapter_data:
                sfx_entry.insert(0, chapter_data["sfx"])
            if "reset_health" in chapter_data:
                reset_health_var.set(chapter_data["reset_health"])
            if "cutscenes" in chapter_data:
                cutscenes_data.extend(chapter_data["cutscenes"])
                refresh_cutscenes_list()
            if "positions" in chapter_data:
                positions_data.update(chapter_data["positions"])
                refresh_positions_list()

        def save_chapter():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Chapter name cannot be empty!")
                return

            if not chapter_name and new_name in self.data["chapters"]:
                messagebox.showwarning(
                    "Warning", f"Chapter '{new_name}' already exists!"
                )
                return

            chapter_data = {}

            if map_entry.get().strip():
                chapter_data["map"] = map_entry.get().strip()
            if bg_track_entry.get().strip():
                chapter_data["bg_track"] = bg_track_entry.get().strip()
            if bg_entry.get().strip():
                chapter_data["bg"] = bg_entry.get().strip()
            if sfx_entry.get().strip():
                chapter_data["sfx"] = sfx_entry.get().strip()
            if reset_health_var.get():
                chapter_data["reset_health"] = True
            if cutscenes_data:
                chapter_data["cutscenes"] = cutscenes_data.copy()
            if positions_data:
                chapter_data["positions"] = positions_data.copy()

            if chapter_name:
                del self.data["chapters"][chapter_name]

            self.data["chapters"][new_name] = chapter_data
            self.refresh()
            dialog.destroy()

        ttk.Button(scrollable_frame, text="Save", command=save_chapter).grid(
            row=row, column=0, columnspan=2, pady=20
        )

        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

    def delete_chapter(self):
        selection = self.chapters_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select a chapter to delete!")
            return

        chapter_display = self.chapters_listbox.get(selection[0])
        chapter_name = chapter_display.split(" (")[0]

        if messagebox.askyesno("Confirm", f"Delete chapter '{chapter_name}'?"):
            del self.data["chapters"][chapter_name]
            self.refresh()
