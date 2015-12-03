from distutils.core import setup, Extension
import numpy.distutils.misc_util

setup(
    ext_modules=[Extension("morton",
                           ["morton.c"],
                           extra_compile_args=["-march=native"])]
)
