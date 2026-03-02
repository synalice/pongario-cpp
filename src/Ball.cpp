// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Ball.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace pongario {

Ball::Ball(sf::Vector2u window_size) : m_window_size(window_size) {
    m_circle.setRadius(50.0f);
    m_circle.setFillColor(sf::Color::Red);

    m_position.x = static_cast<float>(m_window_size.x) / 2.0f;
    m_position.y = static_cast<float>(m_window_size.y) / 2.0f;
    m_circle.setPosition(m_position);

    m_velocity.x = -800.0f;
    m_velocity.y = -800.0f;
}

void Ball::handle_input(float delta) {
    const float MOVE_SPEED = 1000.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        m_position.x -= MOVE_SPEED * delta;
        if (m_position.x < 0.0f) {
            m_position.x = 0.0f;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        m_position.x += MOVE_SPEED * delta;
        if (m_position.x > static_cast<float>(m_window_size.x)) {
            m_position.x = static_cast<float>(m_window_size.x);
        }
    }

    m_circle.setPosition(sf::Vector2f(m_position));
}

void Ball::set_window_size(sf::Vector2u window_size) {
    m_window_size = window_size;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_circle, states);
}

void Ball::process_physics(float delta) {
    m_position.x += m_velocity.x * delta;
    m_position.y += m_velocity.y * delta;

    const float radius = m_circle.getRadius();
    const float diameter = 2.0f * radius;

    if (m_position.x < 0.0f) {
        m_position.x = 0.0f;
        m_velocity.x = -m_velocity.x;
    } else if (m_position.x + diameter > static_cast<float>(m_window_size.x)) {
        m_position.x = static_cast<float>(m_window_size.x) - diameter;
        m_velocity.x = -m_velocity.x;
    }

    if (m_position.y < 0.0f) {
        m_position.y = 0.0f;
        m_velocity.y = -m_velocity.y;
    } else if (m_position.y + diameter > static_cast<float>(m_window_size.y)) {
        m_position.y = static_cast<float>(m_window_size.y) - diameter;
        m_velocity.y = -m_velocity.y;
    }

    m_circle.setPosition(sf::Vector2f(m_position));
}

} // namespace pongario
