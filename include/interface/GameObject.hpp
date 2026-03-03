// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/Collidable.hpp"
#include "interface/PhysicsProcessor.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace pongario {

class GameObject : public sf::Drawable, public PhysicsProcessor, public Collidable {
  public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;

    ~GameObject() override = default;

    Signal<GameObject &, const sf::FloatRect &> &collision_signal();

  protected:
    void emit_collision_signal();

  private:
    Signal<GameObject &, const sf::FloatRect &> m_collision_signal{};
};

} // namespace pongario
