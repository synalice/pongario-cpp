// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Paddle.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace pongario {

Paddle::Paddle(sf::Vector2u window_size) : m_window_size(window_size) {
    m_rectangle.setSize(sf::Vector2f(300.0f, 30.0f));
    m_rectangle.setFillColor(sf::Color::Green);

    this->reset();
}

void Paddle::process_physics(float delta) {
    const float move_speed = 1000.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        m_position.x -= move_speed * delta;
        if (m_position.x < 0.0f) {
            m_position.x = 0.0f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        m_position.x += move_speed * delta;
        const float max_paddle_position = static_cast<float>(m_window_size.x) - m_rectangle.getSize().x;
        if (m_position.x > static_cast<float>(max_paddle_position)) {
            m_position.x = static_cast<float>(max_paddle_position);
        }
    }

    m_rectangle.setPosition(sf::Vector2f(m_position));

    // Emit collision signal after position update
}

void Paddle::set_window_size(sf::Vector2u window_size) {
    m_window_size = window_size;
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_rectangle, states);
}

sf::FloatRect Paddle::get_bounds() const {
    return m_rectangle.getGlobalBounds();
}

void Paddle::reset() {
    const sf::Vector2f paddle_size = m_rectangle.getSize();
    m_position.x = (static_cast<float>(m_window_size.x) / 2.0f) - (paddle_size.x / 2.0f);
    m_position.y = static_cast<float>(m_window_size.y) / 1.1f;
    m_rectangle.setPosition(m_position);
}

sf::Vector2f Paddle::get_position() const {
    return m_position;
}

} // namespace pongario
