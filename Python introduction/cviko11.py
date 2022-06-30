"""
cviko 11
obrazky
"""

from PIL import Image


def square(size, a):
    im = Image.new("RGB", (size, size), (255,255,255))
    for i in range(a):
        for x in range(a):
            im.putpixel((i+size//2-a//2, x+size//2-a//2), (0,0,0))
    im.save(ctverec, format=None)


def invert_colors(filename):
    im = Image.open(filename)
    width, size = im.size
    for i in range(width):
        for y in range(size):
            (r, g, b) = im.getpixel((i,y))
            im.putpixel((i,y), (255-r,255-g,255-b))
    im.show()


# square(250, 70)
# invert_colors("oops.jpg")
