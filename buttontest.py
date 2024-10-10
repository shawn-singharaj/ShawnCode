import tkinter as tk

def on_button2_click():
    button2.pack_forget()
    button.pack(pady=50)

# Function to be called when the button is clicked
def on_button_click():
    label.config(text="Button Clicked!")
    root.after(3000, change_text)
    button.pack_forget()
    button2.pack(pady=50)


def change_text():
    label.config(text="Press the button!")
    #button.pack(pady=50)
    

# Create the main application window
root = tk.Tk()
root.title("Button to Point")

root.geometry("1080x780")

# Create a label widget
label = tk.Label(root, text="Press the button!")

# Create a button widget
button = tk.Button(root, text="Click me", command=on_button_click)
button2 = tk.Button(root, text="FUck yeah", command=on_button2_click)


# Pack the label and button widgets into the window
label.pack(pady=100)
button.pack(pady=50)

# Run the Tkinter event loop
root.mainloop()