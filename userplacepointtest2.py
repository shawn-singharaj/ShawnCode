import tkinter as tk

def draw_point(event):
    x = event.x
    y = event.y
    canvas.create_oval(x, y, x + 10, y + 10, fill="blue")
    result_label.config(text=f"Point drawn at ({x}, {y})")

# Create the main application window
root = tk.Tk()
root.title("Click to Draw Point Example")

# Create a Canvas widget
canvas = tk.Canvas(root, width=400, height=300)
canvas.pack()

# Bind the draw_point function to the canvas click event
canvas.bind("<Button-1>", draw_point)

# Label to display the result
result_label = tk.Label(root, text="")
result_label.pack()

# Run the Tkinter event loop
root.mainloop()
