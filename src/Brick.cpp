// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Brick.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>

namespace pongario {

Brick::Brick(const BrickConfig &config)
    : m_position(config.position), m_texture(config.texture), m_sprite(*m_texture) {
    m_texture->setSmooth(false);
    m_sprite.setScale(config.scale);
    m_sprite.setPosition(m_position);
}

void Brick::mark_destroyed() {
    m_destroyed = true;
    m_on_destroyed.emit(*this);
}

bool Brick::is_destroyed() const {
    return m_destroyed;
}

sf::FloatRect Brick::get_bounds() const {
    return m_sprite.getGlobalBounds();
}

Signal<Brick &> &Brick::destroyed_signal() {
    return m_on_destroyed;
}

void Brick::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_destroyed) {
        target.draw(m_sprite, states);
    }
}

} // namespace pongario
