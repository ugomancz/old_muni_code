"""
hw5
Ondřej Kostík
469007
"""
from PIL import Image
import math


def black_and_white(picture):       # turns an image to black and white
    im = Image.open(picture).convert("RGB")
    width, height = im.size
    for i in range(width):
        for h in range(height):
            r, g, b = im.getpixel((i, h))
            x = (r+g+b)//3
            im.putpixel((i, h), (x, x, x))
    im.show()


class Turtle:
    def __init__(self, x, y, heading=0):
        self.x = x
        self.y = y
        self.heading = heading
        self.lines = []

    def left(self, angle):      # turning left
        self.heading -= angle

    def right(self, angle):     # turning right
        self.heading += angle

    def forward(self, d):       # going forward
        nx = self.x + d * math.cos(self.heading * math.pi / 180)
        ny = self.y + d * math.sin(self.heading * math.pi / 180)
        self.line_to_turtle(nx, ny)
        self.x, self.y = nx, ny

    def turn_to_turtle(self, turtle):       # turns turtle to another
        x = turtle.x - self.x
        y = turtle.y - self.y
        angle = math.degrees(math.atan(y / x))
        self.heading = angle

    def line_to_turtle(self, nx, ny):       # draws a line between turtles
        self.lines.append((self.x, self.y, nx, ny))


def save_all_turtles(turtles, filename):        # saves shape as .svg file
    f = open(filename, 'w')
    f.write('<svg xmlns="http://www.w3.org/2000/svg">')
    for turtle in turtles:
        for x1, y1, x2, y2 in turtle.lines:
            f.write('<line x1="' + str(x1) + '" y1="' + str(y1) +
                    '" x2="' + str(x2) + '" y2="' + str(y2) + '" ' +
                    'style="stroke:black;stroke-width:1" />')
    f.write('</svg>')
    f.close()


def run_and_catch():        # creates a shape
    run = Turtle(20, 40)
    chase1 = Turtle(0, 20)
    chase2 = Turtle(10, 10)
    chase3 = Turtle(20, 0)
    chase4 = Turtle(0, 60)
    chase5 = Turtle(10, 70)
    chase6 = Turtle(20, 80)
    turtles = [run, chase1, chase2, chase3, chase4, chase5, chase6]
    for _ in range(300):
        run.forward(1)
        chase1.turn_to_turtle(run)
        chase1.forward(1)
        chase2.turn_to_turtle(run)
        chase2.forward(1)
        chase3.turn_to_turtle(run)
        chase3.forward(1)
        chase4.turn_to_turtle(run)
        chase4.forward(1)
        chase5.turn_to_turtle(run)
        chase5.forward(1)
        chase6.turn_to_turtle(run)
        chase6.forward(1)
    save_all_turtles(turtles, "run_and_catch.svg")


def circles():      # creates a shape
    inside = Turtle(400, 400)
    outside = Turtle(400, 457)
    for _ in range(360):
        inside.left(1)
        inside.forward(1)
        outside.line_to_turtle(inside.x, inside.y)
        outside.left(1)
        outside.forward(2)
    turtles = [inside, outside]
    save_all_turtles(turtles, "shape.svg")


# black_and_white("jungle.jpg")
run_and_catch()
circles()
