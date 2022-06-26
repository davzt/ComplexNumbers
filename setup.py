from distutils.core import setup, Extension

setup(name='complexNumbers', version='1.0', \
      ext_modules=[Extension('complexNumbers', ['complexNum.c'])])
