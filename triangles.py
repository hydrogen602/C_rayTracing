#!/usr/bin/python3.7
from __future__ import annotations

import sys
from random import random
from math import sin, cos, pi
import json

class Point:
    def __init__(self, x: float, y: float, z: float):
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, other: Point):
        return Point(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other: Point):
        return Point(self.x - other.x, self.y - other.y, self.z - other.z)

    def __truediv__(self, other: float):
        return Point(self.x / other, self.y / other, self.z / other)
    
    def __str__(self) -> str:
        return f"<{self.x:.02f}, {self.y:.02f}, {self.z:.02f}>"
    
    def toList(self):
        return [self.x, self.y, self.z]

class Triangle:
    def __init__(self, a: Point, b: Point, c: Point):
        self.a = a
        self.b = b
        self.c = c
    
    def __str__(self) -> str:
        return f"A = {self.a}, B = {self.b}, C = {self.c}"
    
    def toList(self):
        return [self.a.toList(), self.b.toList(), self.c.toList()]

    def sierpinski(self, randRange: float):
        AB = (self.b - self.a) / 2 + self.a
        BC = (self.b - self.c) / 2 + self.c
        CA = (self.c - self.a) / 2 + self.a

        AB.z += (random() - 0.5) * randRange
        BC.z += (random() - 0.5) * randRange
        CA.z += (random() - 0.5) * randRange

        # 1 triangle -> 4 triangles
        #       
        #      C
        #     / \
        #    /   \
        #   /     \
        #  A-------B
        #
        #      C
        #     / \
        #    CA  BC
        #   /     \
        #  A--BA---B
        #
        # new triangles:
        #
        # CA BC BA
        #  A CA BA
        #  C CA BC
        #  B BA BC
        #
        return [
            Triangle(AB, BC, CA),
            Triangle(self.a, AB, CA),
            Triangle(self.b, AB, BC),
            Triangle(self.c, CA, BC)
            ]

def fractal(n: int = 2):
    t = Triangle(Point(10, 10, -5), Point(10, -10, -5), Point(-10, 0, -5))
    ls = [t]
    for i in range(n):
        newLs = []
        for tri in ls:
            newLs += tri.sierpinski(2.0)
        ls = newLs

    ls = [i.toList() for i in ls]

    f = open("triangles.json", "w")
    json.dump(ls, f, indent=1)
    f.close()


if __name__ == "__main__":
    if (len(sys.argv) != 2):
        fractal()
    else:
        fractal(int(sys.argv[1]))

    