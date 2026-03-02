// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "PhysicsProcessor.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace pongario {

class GameObject : public sf::Drawable, public PhysicsProcessor {
  public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
    virtual void process_physics(float delta) override {};
};

} // namespace pongario
