#!/usr/bin/env python

from distutils.core import setup, Extension
import sys
import os
from os.path import join

program_files = os.getenv('PROGRAMFILES')
platform = sys.platform.lower()

libraries = ['dpf', 'usb']
extra_link_args = []
extra_compile_args = []

print("***********************************")
print("***** Platform =%s"%(platform))
print("***********************************")


include_dirs=['dpf-ax/dpflib','dpf-ax/include']
library_dirs=['dpf-ax/dpflib']

if -1 != platform.find("win32"):
    print("*** WIN 32 Platform ***")
    libraries = ["libusb","libdpf"]
    extra_link_args = ['/LIBPATH:' + join(program_files, 'Libusb-win32', 'lib', 'msvc')]
    extra_compile_args = ['/I' + join(program_files, 'Libusb-win32', 'include')]
else:
    print("*** Assuming GNU/Linux Platform ***")

dpfmodule = Extension(name = 'dpflib',
                    libraries = libraries,
                    library_dirs=library_dirs,
                    include_dirs=include_dirs,
                    sources = ['py_device.c'],
                    extra_link_args = extra_link_args,
                    extra_compile_args = extra_compile_args
                    )

setup(name = 'pydpflib',
    version = '0.13',
    description = "DPF access extension module",
    long_description =
    """
    pydpflib provides DPF access to python, with interface to show RGB images on DPF directly.
    This is a fork of hackfin's dpf-ax version at http://sourceforge.net/projects/dpf-ax
    """,
    author = 'Martin Strubel/ BoeserFisch / Jens Koehler',
    author_email = 'irimi@gmx.de',
    url = 'http://sourceforge.net/projects/pydpf',
    license = 'LGPLv2',
    ext_modules = [dpfmodule])
