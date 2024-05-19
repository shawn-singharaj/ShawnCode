import tkinter as tk
import yaml

class RaceCarTrackApp:
    # initialized function
    def __init__(self, master):
        self.master = master
        self.master.title("Race Car Track Designer")
        self.master.geometry("1080x720")

        # create canvas, screen dimensions 1000x700, can change
        self.canvas = tk.Canvas(self.master, width=1000, height=700, bg="white")
        self.canvas.pack()

        height = 50
        width = 50
        
        # create lines for grid
        for i in range(0, 13):
            self.canvas.create_line(0, height, 1000, height)
            self.canvas.create_text(10, height + 5, text=int(height / 10))
            height += 50

        for i  in range(0, 19):
            self.canvas.create_line(width, 0, width, 700)
            self.canvas.create_text(width + 10, 10, text=int(width / 10))
            width += 50

        self.color_var = tk.StringVar(value="blue")

        # create buttons
        self.blue_button = tk.Button(self.master, text="Blue", command=lambda: self.set_color("blue"), bg=("Blue"), fg=("White"))
        self.yellow_button = tk.Button(self.master, text="Yellow", command=lambda: self.set_color("yellow"), bg=("yellow"), fg=("Black"))
        self.orange_button = tk.Button(self.master, text="Orange", command=lambda: self.set_color("orange"), bg=("Orange"), fg=("White"))
        self.show_coordinates_button = tk.Button(self.master, text="Show Coordinates", command=self.show_coordinates, bg=("green"), fg=("white"))
        self.car_button = tk.Button(self.master, text="Starting Point", command=lambda: self.set_color("red"), bg =("red"), fg = ("white"))
        
        # place buttons
        self.blue_button.pack(side=tk.LEFT, padx=5)
        self.yellow_button.pack(side=tk.LEFT, padx=5)
        self.orange_button.pack(side=tk.LEFT, padx=5)
        self.show_coordinates_button.pack(side=tk.LEFT, padx=5)
        self.car_button.pack(side=tk.LEFT, padx=5)

        # intialize dots tuple
        self.dots = []

        # set keybinds
        self.canvas.bind("<Button-1>", self.place_dot)
        self.canvas.bind("<Button-3>", self.remove_dot)  # right mouse button click

        # intitialize all_coords to be exported to YAML
        self.all_coords = {
            'cones_left': [],
            'cones_right': [],
            'cones_orange': [],
            'cones_orange_big':[],
            'tk_device':[],
            'starting_pose_front_wing': [0.0, 0.0, 0.0],
            'lap_threshold':180
        }

    # color changes
    def set_color(self, color):
        self.color_var.set(color)

    # place dot function
    def place_dot(self, event):
        #sets x and y coordinates for each dot placed
        x, y = event.x, event.y

        # color of dot ref. line 48
        color = self.color_var.get()
        dot_size = 4

        # drawing the actual dot
        self.canvas.create_oval(x - dot_size, y - dot_size, x + dot_size, y + dot_size, fill=color, tags="dots")

        # dot coordinates + color stored
        self.dots.append((x, y, color))

    # right click removes dot
    def remove_dot(self, event):
        x, y = event.x, event.y
        # find and remove the closest dot based on the clicked position
        closest_dot = min(self.dots, key=lambda dot: ((dot[0] - x)**2 + (dot[1] - y)**2)**0.5)
        self.dots.remove(closest_dot)

        # refresh canvas function
        self.refresh_canvas()

    # refresh canvas 
    def refresh_canvas(self):
        self.canvas.delete("dots")
        for dot in self.dots:
            x, y, color = dot
            dot_size = 4
            self.canvas.create_oval(x - dot_size, y - dot_size, x + dot_size, y + dot_size, fill=color, tags="dots")

    # displays a separate window
    def show_coordinates(self):
        # creates a separate window
        coordinates_window = tk.Toplevel(self.master)
        coordinates_window.title("Dot Coordinates")
        
        frame = tk.Frame(coordinates_window)
        frame.pack(fill=tk.BOTH, expand=True)

        # create a canvas widget
        canvas = tk.Canvas(frame)
        canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        # create a scrollbar widget
        scrollbar = tk.Scrollbar(frame, orient=tk.VERTICAL, command=canvas.yview)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        # configure the canvas to use the Scrollbar
        canvas.configure(yscrollcommand=scrollbar.set)
        canvas.bind('<Configure>', lambda e: canvas.configure(scrollregion = canvas.bbox("all")))

        second_frame = tk.Frame(canvas)

        canvas.create_window((0,0), window=second_frame, anchor="ne")

        # print out all coords in terminal
        print("running all_coords:")
        self.all_coords = {
            'cones_left': [],
            'cones_right': [],
            'cones_orange': [],
            'cones_orange_big':[],
            'tk_device':[],
            'starting_pose_front_wing': [0.0, 0.0, 0.0],
            'lap_threshold':180
        }          

        i = 0
        # red dot intialized to 0, 0
        for x, y, color in self.dots:
            if color == "red":
                first_dot = self.dots[i]
                x1 = first_dot[0]
                y1 = first_dot[1]
            else:
                first_dot = self.dots[0]
                x1 = first_dot[0]
                y1 = first_dot[1]
            i += 1

        # adjusts each dot in relation to first dot
        for x, y, color in self.dots:
            x2 = x - x1
            y2 = y - y1
            
            if color == "red":
                print(x, y)
                print(x2, y2) 
                print((x2 / 10), (y2 / 10))

            if color == "blue":
                print(x, y)
                print(x2, y2)
                print((x2 / 10), (y2 / 10))
                
            if color == "orange":
                print(x, y)
                print(x2, y2)
                print((x2 / 10), (y2 / 10))

            if color == "yellow":
                print(x, y)
                print(x2, y2)
                print((x2 / 10), (y2 / 10))

        # what user sees when button clicked
        blue_coordinates = [f"- - {(x - x1) / 10}\n -  {(y - y1) / 10}" for x, y, color in self.dots if color == "blue"]
        yellow_coordinates = [f"- - {(x - x1) / 10}\n -  {(y - y1) / 10}" for x, y, color in self.dots if color == "yellow"]
        orange_coordinates = [f"- - {(x - x1) / 10}\n -  {(y - y1) / 10}" for x, y, color in self.dots if color == "orange"]
        red_coordinates = [f"- - {(x - x1) / 10}\n -  {(y - y1) / 10}" for x, y, color in self.dots if color == "red"]

        # for YAML, pixels / 10 = meter
        blue_x_coordinates = [((x - x1) / 10) for x, _, color in self.dots if color == "blue"]
        blue_y_coordinates = [((y - y1) / 10) for _, y, color in self.dots if color == "blue"]
        yellow_x_coordinates = [((x - x1) / 10) for x, _, color in self.dots if color == "yellow"]
        yellow_y_coordinates = [((y - y1) / 10) for _, y, color in self.dots if color == "yellow"]
        orange_x_coordinates = [((x - x1) / 10) for x, _, color in self.dots if color == "orange"]
        orange_y_coordinates = [((y - y1) / 10) for _, y, color in self.dots if color == "orange"]
       
        # each color's x and y coordinates appended
        for (x, y) in zip(blue_x_coordinates, blue_y_coordinates):
            self.all_coords['cones_left'].append([x,y])

        for (x, y) in zip(yellow_x_coordinates, yellow_y_coordinates):
            self.all_coords['cones_right'].append([x,y])

        for (x, y) in zip(orange_x_coordinates, orange_y_coordinates):
            self.all_coords['cones_orange_big'].append([x,y])

        # create label widgets for the three colored cones
        bluee_label = tk.Label(second_frame, text="Blue:")
        blue_label = tk.Label(second_frame, text="\n".join(blue_coordinates))
        yelloww_label = tk.Label(second_frame, text="\nYellow:")
        yellow_label = tk.Label(second_frame, text="\n" .join(yellow_coordinates))
        orangee_label = tk.Label(second_frame, text="\nOrange:")
        orange_label = tk.Label(second_frame, text="\n".join(orange_coordinates))
        redd_label = tk.Label(second_frame, text="\nRed:")
        red_label = tk.Label(second_frame, text="\n" .join(red_coordinates))
        export_to_yaml_button = tk.Button(second_frame, text="Export to YAML", command=self.export_to_yaml)

        # Update the scroll region of the Canvas
        canvas.update_idletasks()
        canvas.config(scrollregion=canvas.bbox("all"))

        # display/place the labels and "Export to YAML" button
        export_to_yaml_button.pack()
        bluee_label.pack()
        blue_label.pack()
        yelloww_label.pack()
        yellow_label.pack()
        orangee_label.pack()
        orange_label.pack()
        redd_label.pack()
        red_label.pack()
        

    # dumps the self.all_coords into a YAML file called "race_track_coordinates.yaml"
    def export_to_yaml(self):
        with open("race_track_coordinates.yaml", "w") as yaml_file:
            yaml.dump(self.all_coords, yaml_file, default_flow_style=False)
        print(open('race_track_coordinates.yaml').read())

# create window
root = tk.Tk()

# refer window to RaceCarTrackApp class
app = RaceCarTrackApp(root)

# run that jawn
root.mainloop()
