// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Paddle.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace pongario {

Paddle::Paddle(sf::Vector2u window_size)
    : m_window_size(window_size) {
    m_rectangle.setSize(sf::Vector2f(50.0f, 50.0f));
    m_rectangle.setFillColor(sf::Color::Green);

    m_position.x = static_cast<float>(m_window_size.x) / 2.0f;
    m_position.y = static_cast<float>(m_window_size.y) / 2.0f;
    m_rectangle.setPosition(m_position);
}

void Paddle::handle_input(float delta) {
    const float move_speed = 1000.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        m_position.x -= move_speed * delta;
        if (m_position.x < 0.0f) {
            m_position.x = 0.0f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        m_position.x += move_speed * delta;
        if (m_position.x > static_cast<float>(m_window_size.x)) {
            m_position.x = static_cast<float>(m_window_size.x);
        }
    }

    m_rectangle.setPosition(sf::Vector2f(m_position));
}

void Paddle::set_window_size(sf::Vector2u window_size) {
    m_window_size = window_size;
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_rectangle, states);
}

} // namespace pongario
