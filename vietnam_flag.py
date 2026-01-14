import turtle
import time
import math

screen = turtle.Screen()
screen.setup(width=700, height=500)
screen.bgcolor("white")
pen = turtle.Turtle()
pen.speed(3)
pen.pensize(3)

width = 600
height = 400
top_left = (-width // 2, height // 2)

pen.penup()
pen.goto(top_left)
pen.pendown()
pen.color("black")

for _ in range(2):
    pen.forward(width)
    pen.right(90)
    pen.forward(height)
    pen.right(90)

pen.penup()
pen.goto(top_left[0] + 1, top_left[1] - 1)
pen.color("red")
pen.begin_fill()
pen.pendown()

for _ in range(2):
    pen.forward(width - 2)
    pen.right(90)
    pen.forward(height - 2)
    pen.right(90)

pen.end_fill()
pen.penup()

center_x = top_left[0] + width / 2
center_y = top_left[1] - height / 2

pen.color("yellow")
pen.begin_fill()

r_outer = 80
r_inner = r_outer * math.sin(math.radians(18)) / math.sin(math.radians(126))
points = []

rotation_offset = 90

for i in range(10):
    angle = math.radians(i * 36 + rotation_offset)
    r = r_outer if i % 2 == 0 else r_inner
    x = center_x + r * math.cos(angle)
    y = center_y + r * math.sin(angle)
    points.append((x, y))

pen.penup()
pen.goto(points[0])
pen.pendown()
for p in points[1:]:
    pen.goto(p)
    time.sleep(0.1) 
pen.goto(points[0])
pen.end_fill()

pen.hideturtle()
turtle.done()
