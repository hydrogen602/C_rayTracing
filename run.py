import main

import sys

size = 500

if len(sys.argv) > 1:
    if sys.argv[1].isnumeric():
        size = int(sys.argv[1])
    else:
        print("Argument 1 should be of type int")


sc = main.Scene(size)
rgb = sc.generateImagePixels()

import png

f = open('test.png', 'wb')      # binary mode is important
w = png.Writer(size, size, greyscale=False)
w.write(f, rgb)
f.close()

