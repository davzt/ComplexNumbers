from distutils.core import setup, Extension

module = Extension(
      'complex_numbers',
      sources=['main.c', 'complexNum.c']
)

setup(
      name='complex_numbers',
      version='1.0',
      description='',
      ext_modules=[module]
)