// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Brick.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

namespace pongario {

Brick::Brick(const BrickConfig &config)
    : m_position(config.position) {
    m_rectangle.setSize(config.size);
    m_rectangle.setFillColor(config.color);
    m_rectangle.setPosition(m_position);
}

void Brick::mark_destroyed() {
    m_destroyed = true;
    m_on_destroyed.emit(*this);
}

bool Brick::is_destroyed() const {
    return m_destroyed;
}

sf::FloatRect Brick::get_bounds() const {
    return m_rectangle.getGlobalBounds();
}

Signal<Brick &> &Brick::destroyed_signal() {
    return m_on_destroyed;
}

void Brick::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_destroyed) {
        target.draw(m_rectangle, states);
    }
}

} // namespace pongario
