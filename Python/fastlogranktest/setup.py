#!/usr/bin/env python
# -*- coding: utf-8 -*-


try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

from distutils.extension import Extension
from Cython.Build import cythonize
import numpy


source_files = ["fastlogranktest/fastlogranktest.pyx"]
include_dirs = [numpy.get_include()]
extensions = [Extension("fastlogranktest.fastlogranktest",
                        sources=source_files,
                        include_dirs=include_dirs)]
                        
with open('README.rst') as readme_file:
    readme = readme_file.read()

with open('HISTORY.rst') as history_file:
    history = history_file.read().replace('.. :changelog:', '')

requirements = ['cython', 'numpy']


setup(
    name='fastlogranktest',
    version='0.2.1',
    description="Perform the Log-Rank-Test very fast",
    long_description=readme + '\n\n' + history,
    author="Andreas Stelzer, Manuela Lautizi, Tim Kacprowski, Research group of computational systems medicine Chair of Experimental Bioinformatics TU Munich",
    author_email='ga63nep@mytum.de, manuela.lautizi@wzw.tum.de, tim.kacprowski@wzw.tum.de',
    url='https://github.com/compsysmed/fastlogranktest.git',
    packages=[
        'fastlogranktest',
    ],
    package_dir={'fastlogranktest':
                 'fastlogranktest'},
    package_data={'': ['*.pyx', '*.pxd', '*.h', '*.c', '*.hpp', '*.cpp', '*.txt', '*.dat', '*.csv']},
    install_requires=requirements,
    license="BSD",
    zip_safe=False,
    keywords='fastlogranktest',
    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: BSD License',
        'Natural Language :: English',
        'Programming Language :: Cython',
        "Programming Language :: Python :: 2",
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
    ],
    test_suite='tests',
    ext_modules=cythonize(extensions, language_level="3"),
)