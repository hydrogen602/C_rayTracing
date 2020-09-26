from triangles import Point, Triangle
import math


def makeCircle(radius, height):
    # return list of triangles
    circularPointCount = 20

    center = Point(0, 0, 0)

    points = []
    for i in range(circularPointCount):
        angle = (math.pi*2/circularPointCount) * i
        x = math.cos(angle) * radius
        z = math.sin(angle) * radius
        y = z / 3
        points.append(Point(x, y, z))
    
    triangles = []
    for p1, p2 in zip(points, points[1:] + points[:1]):
        triangles.append(Triangle(p1, p2, center))
    
    renderTriangles(triangles)



#!/usr/bin/python3.7
import main

import sys
import json

# triangles = np.array(json.load(ft), dtype=np.double)
# triangles = triangles.reshape((len(triangles), 9))

def renderTriangles(lstTriangles, size=500, fileOut='test.png'):
    # lstTriangles is List[Triangle]
    print('Rendering {} triangles'.format(len(lstTriangles)))

    tArray = main.TriangleArray(len(lstTriangles))

    for i, t in enumerate(lstTriangles):
        tArray[i] = t.toList()

    sc = main.Scene(size, tArray)
    rgb = sc.generateImagePixels()
    print("Ray Tracing Done")

    import png

    w = png.Writer(size, size, greyscale=False)
    with open(fileOut, 'wb') as f: # binary mode is important according to pypng docs
        w.write(f, rgb)


if __name__ == '__main__':
    makeCircle(5, 0)