# editor-main.py

import tkinter as tk
from tkinter import ttk, messagebox
import json
import os
import csv

# Import the tab classes
from tabs.animations import AnimationsTab
from tabs.items import ItemsTab
from tabs.objects import ObjectsTab
from tabs.cutscenes import CutscenesTab
from tabs.actions import ActionsTab
from tabs.chapters import ChaptersTab
from tabs.dialogue import DialogueTab
from tabs.maps import MapsTab  # This import is correct

full_source = ""

with open("editor-main.py", "r") as f:
    full_source = "editor-main.py:\n" + f.read()

for file in os.listdir("tabs"):
    if file.endswith(".py"):
        with open(os.path.join("tabs", file), "r") as f:
            full_source += "\n\ntabs/" + file + ":\n" + f.read()

with open("full-source-editor.txt", "w") as f:
    f.write(full_source)


class HeadersEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("Glass Eyes Editor")
        self.root.geometry("1400x800")

        self.filename = "headers.json"
        self.dialogue_filename = "dialogue.tsv"

        self.data = self.load_json_data()
        self.dialogue_data = self.load_dialogue_data()
        self.dialogue_modified = False

        # Create menu bar
        menubar = tk.Menu(root)
        root.config(menu=menubar)

        file_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="Save", command=self.save_all_data)
        file_menu.add_command(label="Reload", command=self.reload_all_data)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=root.quit)

        # Create notebook (tabbed interface)
        self.notebook = ttk.Notebook(root)
        self.notebook.pack(fill="both", expand=True, padx=5, pady=5)

        # Create tabs by instantiating them
        self.tabs = []
        self.tabs.append(AnimationsTab(self.notebook, self))
        self.tabs.append(ItemsTab(self.notebook, self))
        self.tabs.append(ObjectsTab(self.notebook, self))
        self.tabs.append(CutscenesTab(self.notebook, self))
        self.tabs.append(ActionsTab(self.notebook, self))
        self.tabs.append(ChaptersTab(self.notebook, self))
        self.tabs.append(DialogueTab(self.notebook, self))
        self.tabs.append(MapsTab(self.notebook, self))  # Add the Maps tab

        # --- MODIFICATION: Find the MapsTab instance ---
        self.maps_tab_instance = None
        for tab in self.tabs:
            if isinstance(tab, MapsTab):
                self.maps_tab_instance = tab
                break
        # ----------------------------------------------

    # --- Data Access Methods (for tabs) ---

    def get_json_data(self):
        """Returns the main 'headers.json' data dictionary."""
        return self.data

    def get_dialogue_data(self):
        """Returns the main 'dialogue.tsv' data list."""
        return self.dialogue_data

    def mark_dialogue_modified(self):
        """Allows tabs (like DialogueTab) to mark data as dirty."""
        self.dialogue_modified = True

    # --- Data Loading/Saving ---

    def load_json_data(self):
        """Load data from headers.json"""
        if os.path.exists(self.filename):
            with open(self.filename, "r") as f:
                return json.load(f)
        else:
            return {
                "animations": {},
                "items": {},
                "objects": {},
                "cutscenes": {},
                "actions": {"interactable": {}, "automatic": {}},
                "chapters": {},
                # --- MODIFICATION: Removed "maps" key ---
                # "maps": {},
                # ----------------------------------------
            }

    def load_dialogue_data(self):
        """Load data from dialogue.tsv"""
        conversations = []
        try:
            with open(self.dialogue_filename, "r", encoding="utf-8") as f:
                reader = csv.reader(f, delimiter="\t")
                rows = list(reader)

            current_conv = None

            for i, row in enumerate(rows):
                if i == 0:
                    continue  # Skip header
                while len(row) < 16:
                    row.append("")

                if row[0] and all(not cell for cell in row[1:]):
                    if current_conv:
                        conversations.append(current_conv)
                    current_conv = {"name": row[0], "lines": []}
                elif not any(row):
                    continue
                else:
                    if current_conv:
                        current_conv["lines"].append(
                            {
                                "name_id": row[0],
                                "portrait": row[1],
                                "emotion": row[2],
                                "action": row[3],
                                "line1": row[4],
                                "line2": row[5],
                                "line3": row[6],
                                "color": row[7],
                                "size": row[8],
                                "speed": row[9],
                                "index": row[10],
                                "anim": row[11],
                                "navigate": row[12],
                                "branching1": row[13],
                                "branching2": row[14],
                                "bg_pointer": row[15],
                            }
                        )

            if current_conv:
                conversations.append(current_conv)

            self.dialogue_modified = False
            return conversations

        except FileNotFoundError:
            messagebox.showwarning(
                "File Not Found",
                f"{self.dialogue_filename} not found. Starting with empty dialogue.",
            )
            return []
        except Exception as e:
            messagebox.showerror(f"Error loading dialogue file: {str(e)}")
            return []

    def save_all_data(self):
        """Save data to headers.json, dialogue.tsv, and individual map files"""
        try:
            # Save JSON data
            with open(self.filename, "w") as f:
                json.dump(self.data, f, indent=4)

            # Save Dialogue data
            with open(self.dialogue_filename, "w", encoding="utf-8", newline="") as f:
                writer = csv.writer(f, delimiter="\t")
                writer.writerow(
                    [
                        "Name / ID",
                        "Portrait",
                        "Emotion",
                        "Action",
                        "Line1",
                        "Line2",
                        "Line3",
                        "Color",
                        "Size",
                        "Speed",
                        "Index",
                        "Anim",
                        "Navigate",
                        "Branching Dialogue 1",
                        "Branching Dialogue 2",
                        "Bg Pointer",
                    ]
                )
                for i, conv in enumerate(self.dialogue_data):
                    if i > 0:
                        writer.writerow([""] * 16)
                    writer.writerow([conv["name"]] + [""] * 15)
                    for line in conv["lines"]:
                        writer.writerow(
                            [
                                line.get("name_id", ""),
                                line.get("portrait", ""),
                                line.get("emotion", ""),
                                line.get("action", ""),
                                line.get("line1", ""),
                                line.get("line2", ""),
                                line.get("line3", ""),
                                line.get("color", ""),
                                line.get("size", ""),
                                line.get("speed", ""),
                                line.get("index", ""),
                                line.get("anim", ""),
                                line.get("navigate", ""),
                                line.get("branching1", ""),
                                line.get("branching2", ""),
                                line.get("bg_pointer", ""),
                            ]
                        )

            # --- MODIFICATION: Tell MapsTab to save its files ---
            if self.maps_tab_instance and hasattr(self.maps_tab_instance, 'save_all_maps_to_files'):
                self.maps_tab_instance.save_all_maps_to_files()
            # ----------------------------------------------------

            self.dialogue_modified = False
            messagebox.showinfo("Success", "All files saved successfully!")

        except Exception as e:
            messagebox.showerror("Error", f"Failed to save files: {str(e)}")

    def reload_all_data(self):
        """Reload data from all files"""
        self.data = self.load_json_data()
        self.dialogue_data = self.load_dialogue_data()
        
        # --- MODIFICATION: Tell MapsTab to reload its files ---
        if self.maps_tab_instance and hasattr(self.maps_tab_instance, 'load_all_maps_from_files'):
            self.maps_tab_instance.load_all_maps_from_files()
        # ------------------------------------------------------
        
        self.refresh_all_tabs()
        messagebox.showinfo("Success", "Data reloaded!")

    def refresh_all_tabs(self):
        """Refresh all tab displays"""
        for tab in self.tabs:
            if hasattr(tab, "refresh"):
                tab.refresh()


if __name__ == "__main__":
    root = tk.Tk()
    app = HeadersEditor(root)
    root.mainloop()