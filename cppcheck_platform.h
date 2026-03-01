// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

/**
 * The purpose of this file is to fix "This operating system is not supported by SFML library"
 * error when running `cppcheck`.
 */

#define __linux__ 1
#define __unix__ 1
