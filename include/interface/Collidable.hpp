// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <SFML/Graphics/Rect.hpp>

namespace pongario {

class Collidable {
  public:
    virtual ~Collidable() = default;
    virtual sf::FloatRect get_bounds() const = 0;
};

} // namespace pongario
