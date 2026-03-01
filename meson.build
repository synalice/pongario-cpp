# SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
#
# SPDX-License-Identifier: MIT

project(
    'pongario-cpp',
    'cpp',
    version: '1.0.0',
    license: 'MIT',
    license_files: ['LICENSE'],
    meson_version: '>=1.9.1',
    default_options: [
        'warning_level=3',
        'buildtype=debugoptimized',
        'cpp_std=c++20',
        'werror=true',
    ],
)

description = 'A "Atari Breakout"-like game writen in C++ and SFML'
project_root = meson.current_source_dir()

add_project_arguments(
    '-pedantic',
    '-Werror=implicit',
    '-Werror=incompatible-pointer-types',
    '-Werror=int-conversion',
    '-Wshadow',
    '-Wconversion',
    '-Wsign-conversion',
    '-Wcast-align',
    '-Wformat',
    '-Wformat=2',
    '-Wformat-security',
    '-Wnull-dereference',
    '-Wstrict-prototypes',
    '-Wmissing-prototypes',
    '-Wmissing-include-dirs',
    '-Wold-style-definition',
    '-Wunreachable-code',
    '-Wno-unused-parameter',
    '-Wwrite-strings',
    '-Wredundant-decls',
    '-Wnested-externs',
    '-Wimplicit-fallthrough',
    '-fstack-clash-protection',
    '-fstack-protector-strong',
    '-fstrict-flex-arrays=3',
    language: 'cpp',
)

sfml = dependency('sfml-all')

subdir('include')
subdir('src')
