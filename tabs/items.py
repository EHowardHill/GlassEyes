# tab_items.py

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog


class ItemsTab:
    def __init__(self, notebook, app):
        self.app = app
        self.root = app.root
        self.data = app.get_json_data()

        self.frame = ttk.Frame(notebook)
        notebook.add(self.frame, text="Items")

        self.create_widgets()
        self.refresh()

    def create_widgets(self):
        ttk.Label(self.frame, text="Items:", font=("Arial", 10, "bold")).pack(pady=5)

        self.items_listbox = tk.Listbox(self.frame, height=20)
        self.items_listbox.pack(fill="both", expand=True, padx=5)

        btn_frame = ttk.Frame(self.frame)
        btn_frame.pack(fill="x", padx=5, pady=5)
        ttk.Button(btn_frame, text="Add Item", command=self.add_item).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Edit Item", command=self.edit_item).pack(
            side="left", padx=2
        )
        ttk.Button(btn_frame, text="Delete Item", command=self.delete_item).pack(
            side="left", padx=2
        )

    def refresh(self):
        """Renamed from refresh_items"""
        self.items_listbox.delete(0, tk.END)
        for item in self.data.get("items", {}).keys():
            props = self.data["items"][item]
            display = f"{item}" + (
                f" (drop: {props.get('drop')})" if props.get("drop") is not None else ""
            )
            self.items_listbox.insert(tk.END, display)

    def add_item(self):
        self.edit_item_dialog(None)

    def edit_item(self):
        selection = self.items_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an item to edit!")
            return

        item_display = self.items_listbox.get(selection[0])
        item_name = item_display.split(" (")[0]
        self.edit_item_dialog(item_name)

    def edit_item_dialog(self, item_name):
        dialog = tk.Toplevel(self.root)
        dialog.title("Edit Item" if item_name else "Add Item")
        dialog.geometry("350x150")

        ttk.Label(dialog, text="Item Name:").grid(
            row=0, column=0, sticky="w", padx=5, pady=5
        )
        name_entry = ttk.Entry(dialog, width=30)
        name_entry.grid(row=0, column=1, padx=5, pady=5)

        ttk.Label(dialog, text="Drop:").grid(
            row=1, column=0, sticky="w", padx=5, pady=5
        )
        drop_var = tk.BooleanVar()
        drop_check = ttk.Checkbutton(dialog, variable=drop_var)
        drop_check.grid(row=1, column=1, sticky="w", padx=5, pady=5)

        if item_name:
            name_entry.insert(0, item_name)
            if "drop" in self.data["items"][item_name]:
                drop_var.set(self.data["items"][item_name]["drop"])

        def save_item():
            new_name = name_entry.get().strip()
            if not new_name:
                messagebox.showwarning("Warning", "Item name cannot be empty!")
                return

            if item_name and item_name != new_name:
                del self.data["items"][item_name]

            item_data = {}
            if drop_var.get():
                item_data["drop"] = True

            self.data["items"][new_name] = item_data
            self.refresh()
            dialog.destroy()

        ttk.Button(dialog, text="Save", command=save_item).grid(
            row=2, column=0, columnspan=2, pady=20
        )

    def delete_item(self):
        selection = self.items_listbox.curselection()
        if not selection:
            messagebox.showwarning("Warning", "Please select an item to delete!")
            return

        item_display = self.items_listbox.get(selection[0])
        item_name = item_display.split(" (")[0]

        if messagebox.askyesno("Confirm", f"Delete item '{item_name}'?"):
            del self.data["items"][item_name]
            self.refresh()
