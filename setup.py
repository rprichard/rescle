# -*- coding: utf-8 -*-
from distutils.core import setup, Extension

setup(
	name='rescle',
	version='1.0',
	description='Rescle(RESource Command Line Editor) is not a resource compiler, but poweful tool for Windows application developers. ',
	author='OKUMURA Yoshio',
	author_email='yoshio.okumura@gmail.com',
	ext_modules = [
		Extension('_rescle', ['rescle.i', 'rescle.cpp'],
			library_dirs=[],
			libraries=[],
			extra_compile_args=['/D_UNICODE', '/DUNICODE'],
			extra_link_args=[])
		])
