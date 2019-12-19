# cython: language_level=3

from __future__ import print_function

from libc.stdlib cimport calloc, free

import numpy as np

cimport numpy as np

DTYPE = np.int8

ctypedef np.int8_t DTYPE_t

ctypedef unsigned char byte

cdef extern from "dataTypes/dataTypes.h":
    ctypedef struct vect3_t:
        double x
        double y
        double z
    ctypedef struct sphere_t:
        vect3_t n
        double d
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
    void initScene(scene_t *, unsigned int size)
    int generateImage(byte* rgb, scene_t * sc)

cdef class Scene:
    cdef scene_t * sc
    cdef unsigned int size

    def __init__(self, unsigned int sz):
        self.size = sz
        initScene(self.sc, sz)

    def __cinit__(self):
        self.sc = <scene_t *>calloc(1, sizeof(scene_t))

    def __dealloc__(self):
        free(<void *>self.sc)

    def generateImagePixels(self):

        cdef np.ndarray[byte, ndim=2, mode="c"] rgb = np.zeros((self.size, self.size * 3), dtype=np.uint8)

        generateImage(&rgb[0,0], self.sc)

        return rgb
