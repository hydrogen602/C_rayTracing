from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy as np

ext_modules = [
    Extension("main",
              sources=["interface.pyx", "array.c", "grid.c", "pythonInterface.c", "dataTypes/dColor.c", "dataTypes/ray.c", "dataTypes/sphere.c",  "dataTypes/vect3.c"]
              )
    ]

setup(
    include_dirs = [np.get_include()],
    ext_modules = cythonize(ext_modules, annotate=True)
)