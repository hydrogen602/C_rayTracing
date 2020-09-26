# cython: language_level=3

from __future__ import print_function

from libc.stdlib cimport calloc, free

import numpy as np

cimport numpy as np

DTYPE = np.int8

ctypedef np.int8_t DTYPE_t

ctypedef unsigned char byte

cdef extern from "dataTypes/dataTypes.h":
    ctypedef struct dColor_t:
        double r
        double g
        double b
    ctypedef struct vect3_t:
        double x
        double y
        double z
    ctypedef struct sphere_t:
        vect3_t n
        double d
        dColor_t color
    ctypedef struct triangle_t:
        vect3_t a
        vect3_t b
        vect3_t c
        vect3_t n
        double d
        dColor_t color
    ctypedef struct grid_t:
        vect3_t src
        vect3_t forward
        vect3_t up
        vect3_t left
        vect3_t centerOfGrid
        vect3_t topLeftCorner
        vect3_t bottomRightCorner
        vect3_t rightStepVector
        vect3_t downStepVector
        unsigned int size
    ctypedef struct scene_t:
        grid_t grid
        sphere_t * geometry # length of array is stored in memory block
        vect3_t lsrc # light source


cdef extern from "pythonInterface.h":
    void initScene(scene_t *, unsigned int size, triangle_t * tri, unsigned int triLen) #, triangle_t* tri, unsigned int numOfTriangles)
    int generateImage(byte* rgb, scene_t * sc)
    void initTriangle(triangle_t * t, double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)

cdef class TriangleArray:
    cdef triangle_t * tr
    cdef unsigned int length

    def __setitem__(self, unsigned int key, value):
        if len(value) != 9:
            raise Exception("Needs 9 valus, got " + str(len(value) + " values"))
        if key < 0 or key >= self.length:
            raise IndexError("index out of bouds")
        
        # points a list of len 3 pls
        initTriangle(self.tr + key, value[0], value[1], value[2], 
            value[3], value[4], value[5], 
            value[6], value[7], value[8])
    
    def __cinit__(self, unsigned int length):
        self.length = length
        self.tr = <triangle_t *>calloc(length, sizeof(triangle_t))

    def __dealloc__(self):
        free(<void *>self.tr)

cdef class Scene:
    cdef scene_t * sc
    cdef unsigned int size

    def __init__(self, unsigned int sz, TriangleArray triangles):
        self.size = sz
        initScene(self.sc, sz, triangles.tr, triangles.length)

    def __cinit__(self):
        self.sc = <scene_t *>calloc(1, sizeof(scene_t))

    def __dealloc__(self):
        free(<void *>self.sc)

    def generateImagePixels(self):

        cdef np.ndarray[byte, ndim=2, mode="c"] rgb = np.zeros((self.size, self.size * 3), dtype=np.uint8)

        generateImage(&rgb[0,0], self.sc)

        return rgb
