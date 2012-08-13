#!/usr/bin/python
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension

module = Extension('xdgmime',
                   sources = ['xdgmime.c',
                              'xdgmime/src/xdgmime.c',
                              'xdgmime/src/xdgmimealias.c',
                              'xdgmime/src/xdgmimecache.c',
                              'xdgmime/src/xdgmimeglob.c',
                              'xdgmime/src/xdgmimeicon.c',
                              'xdgmime/src/xdgmimeint.c',
                              'xdgmime/src/xdgmimemagic.c',
                              'xdgmime/src/xdgmimeparent.c'],
                   include_dirs = ['xdgmime/src/'],
                   define_macros = [('HAVE_MMAP', None)])

setup (name = 'xdgmime',
        version = '1.0',
        ext_modules = [module])

