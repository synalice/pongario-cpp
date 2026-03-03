// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "interface/GameObject.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace pongario {

Signal<GameObject &, const sf::FloatRect &> &GameObject::collision_signal() {
    return m_collision_signal;
}

void GameObject::emit_collision_signal() {
    collision_signal().emit(*this, this->get_bounds());
}

} // namespace pongario
