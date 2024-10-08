import tkinter as tk
from tkinter import simpledialog, filedialog
from PIL import Image, ImageTk

class LEDMatrixEditor:
    def __init__(self, root, num_rows, num_cols):
        self.root = root
        self.root.title("LED Matrix Editor")

        self.num_rows = num_rows
        self.num_cols = num_cols

        self.matrix = [[0 for _ in range(num_cols)] for _ in range(num_rows)]
        
        self.filepath = None

        self.buttons = []
        for row in range(num_rows):
            row_buttons = []
            for col in range(num_cols):
                button = tk.Button(self.root, width=2, height=1, command=lambda r=row, c=col: self.toggle_led(r, c))
                button.grid(row=row, column=col)
                row_buttons.append(button)
            self.buttons.append(row_buttons)

        self.copy_button = tk.Button(self.root, text="Copy Array", command=self.copy_array)
        self.copy_button.grid(row=num_rows, column=0, columnspan=num_cols)

        self.resize_button = tk.Button(self.root, text="Resize Matrix", command=self.resize_matrix)
        self.resize_button.grid(row=num_rows + 1, column=0, columnspan=num_cols)

        self.load_image_button = tk.Button(self.root, text="Load Image", command=self.load_image)
        self.load_image_button.grid(row=num_rows + 2, column=0, columnspan=num_cols)

        self.reload_image_button = tk.Button(self.root, text="Reload Image", command=lambda: self.load_image(self.filepath))
        self.reload_image_button.grid(row=num_rows + 3, column=0, columnspan=num_cols)

        self.image_label = tk.Label(self.root)
        self.image_label.grid(row=num_rows + 3, column=0, columnspan=num_cols)

        self.photo_image = None

    def toggle_led(self, row, col):
        if self.matrix[row][col] == 0:
            self.matrix[row][col] = 1
            self.buttons[row][col].config(bg="red")
        else:
            self.matrix[row][col] = 0
            self.buttons[row][col].config(bg="white")

    def copy_array(self):
        flattened_matrix = [item for sublist in self.matrix for item in sublist]
        print(flattened_matrix)

    def resize_matrix(self):
        new_num_rows = simpledialog.askinteger("Resize Matrix", "Enter the new number of rows:", parent=self.root, minvalue=1)
        new_num_cols = simpledialog.askinteger("Resize Matrix", "Enter the new number of columns:", parent=self.root, minvalue=1)

        if new_num_rows is not None and new_num_cols is not None:
            # Clear the existing matrix and buttons
            for row in self.buttons:
                for button in row:
                    button.destroy()

            # Update the number of rows and columns
            self.num_rows = new_num_rows
            self.num_cols = new_num_cols

            # Recreate the matrix and buttons with the new size
            self.matrix = [[0 for _ in range(new_num_cols)] for _ in range(new_num_rows)]
            self.buttons = []
            for row in range(new_num_rows):
                row_buttons = []
                for col in range(new_num_cols):
                    button = tk.Button(self.root, width=2, height=1, command=lambda r=row, c=col: self.toggle_led(r, c))
                    button.grid(row=row, column=col)
                    row_buttons.append(button)
                self.buttons.append(row_buttons)

            # Update the position of the "Copy Array," "Resize Matrix," "Load Image," and image label
            self.copy_button.grid(row=new_num_rows, column=0, columnspan=new_num_cols)
            self.resize_button.grid(row=new_num_rows + 1, column=0, columnspan=new_num_cols)
            self.load_image_button.grid(row=new_num_rows + 2, column=0, columnspan=new_num_cols)
            self.image_label.grid(row=new_num_rows + 3, column=0, columnspan=new_num_cols)

    def load_image(self, filepath = None):
        file_path = filedialog.askopenfilename(parent=self.root) if filepath == None else filepath
        self.filepath = file_path
        if file_path:
            try:
                image = Image.open(file_path).convert('L')  # Convert to grayscale
                image = image.resize((self.num_cols, self.num_rows))

                self.photo_image = ImageTk.PhotoImage(image=image)
                self.image_label.config(image=self.photo_image)

                # Update the matrix based on pixel intensity
                for row in range(self.num_rows):
                    for col in range(self.num_cols):
                        pixel_value = image.getpixel((col, row))
                        normalized_value = pixel_value / 255.0
                        if normalized_value > 0.5:  # Adjust this threshold as needed
                            self.matrix[row][col] = 1
                            self.buttons[row][col].config(bg="red")
                        else:
                            self.matrix[row][col] = 0
                            self.buttons[row][col].config(bg="white")

            except Exception as e:
                print("Error loading the image:", e)

if __name__ == "__main__":
    initial_num_rows = 8
    initial_num_cols = 8

    root = tk.Tk()
    app = LEDMatrixEditor(root, initial_num_rows, initial_num_cols)
    root.mainloop()
