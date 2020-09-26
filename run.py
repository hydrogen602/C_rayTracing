#!/usr/bin/python3.7
import main

import sys
import json
import numpy as np

size = 500

if len(sys.argv) > 1:
    if sys.argv[1].isnumeric():
        size = int(sys.argv[1])
    else:
        print("Argument 1 should be of type int")

ft = open("triangles.json", "r")
triangles = np.array(json.load(ft), dtype=np.double)
ft.close()

print(triangles.shape)

triangles = triangles.reshape((len(triangles), 9))

print(triangles.shape)

tArray = main.TriangleArray(len(triangles))
for i in range(len(triangles)):
    tArray[i] = triangles[i]

sc = main.Scene(size, tArray)
rgb = sc.generateImagePixels()
print("Ray Tracing Done")

import png

f = open('test.png', 'wb') # binary mode is important according to pypng docs
w = png.Writer(size, size, greyscale=False)
w.write(f, rgb)
f.close()

