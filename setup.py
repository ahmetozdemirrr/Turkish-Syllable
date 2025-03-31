import sys
from setuptools import setup, Extension

# Platform dependent compile flaga
if sys.platform in ["linux", "darwin"]:  # for Linux and macOS
    extra_compile_args = ["-Wall", "-Wextra", "-Werror", "-fPIC"]
elif sys.platform == "win32":  # for Windows
    extra_compile_args = ["/Wall", "/W4", "/WX"]
else:
    extra_compile_args = []  # default for other platforms

# define C extension 
module = Extension(
    "turkish_syllable.libsyllable",
    sources=["turkish_syllable/syllable.c"],
    include_dirs=["include"],
    extra_compile_args=extra_compile_args,
)

# Setup functiion
setup(
    ext_modules=[module],
)