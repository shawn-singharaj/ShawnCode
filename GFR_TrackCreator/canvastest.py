import tkinter as tk

# Create the main application window
root = tk.Tk()
root.title("Point Example")

# Create a Canvas widget
canvas = tk.Canvas(root, width=500, height=500)
canvas.pack()

# Coordinates of the point
x = 300
y = 300

# Draw a point on the Canvas
canvas.create_oval(x, y, x + 5, y + 5, fill="black")  # Using create_oval to draw a small circle (point)

# Run the Tkinter event loop
root.mainloop()