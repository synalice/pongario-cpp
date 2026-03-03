// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <SFML/Graphics/Rect.hpp>

namespace pongario {

class Resettable {
  public:
    virtual ~Resettable() = default;
    virtual void reset() {};
};

} // namespace pongario
