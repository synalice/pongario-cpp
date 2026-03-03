// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Ball.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cmath>

namespace pongario {

Ball::Ball(sf::Vector2u window_size, sf::Vector2f resting_position) : m_resting_position(resting_position), m_window_size(window_size) {
    m_circle.setRadius(RADIUS);
    m_circle.setFillColor(sf::Color::Red);

    this->reset();
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

sf::FloatRect Ball::get_bounds() const {
    return m_circle.getGlobalBounds();
}

void Ball::bounce_vertical(const sf::FloatRect &paddle_bounds) {
    if (m_velocity.y > 0.0f) {
        const float diameter = 2.0f * m_circle.getRadius();
        const float radius = m_circle.getRadius();

        m_position.y = paddle_bounds.position.y - diameter;

        const float ball_center_x = m_position.x + radius;
        const float paddle_center_x = paddle_bounds.position.x + paddle_bounds.size.x / 2.0f;
        const float hit_offset = ball_center_x - paddle_center_x;
        const float normalized_hit = hit_offset / (paddle_bounds.size.x / 2.0f);

        const float current_speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

        const sf::Angle max_angle = sf::degrees(60.0f);
        const sf::Angle bounce_angle = max_angle * normalized_hit;

        m_velocity.x = current_speed * std::sin(bounce_angle.asRadians());
        m_velocity.y = -current_speed * std::cos(bounce_angle.asRadians());

        m_circle.setPosition(m_position);
    }
}

void Ball::bounce_brick(const sf::FloatRect &brick_bounds) {
    const sf::FloatRect ball_bounds = get_bounds();
    const auto intersection = ball_bounds.findIntersection(brick_bounds);

    if (!intersection.has_value()) {
        return;
    }

    // How much the ball is penetrating the brick on each axis
    const sf::Vector2f overlap = intersection->size;

    // Determine whether to resolve collision horizontally or vertically
    bool resolve_x;

    if (overlap.x < overlap.y) {
        // Ball is penetrating more vertically than horizontally
        // This means it hit a vertical side (left/right), so resolve horizontally
        resolve_x = true;
    } else if (overlap.x > overlap.y) {
        // Ball is penetrating more horizontally than vertically
        // This means it hit a horizontal side (top/bottom), so resolve vertically
        resolve_x = false;
    } else {
        // Perfect corner hit - overlaps are equal
        // Use velocity magnitude as tie-breaker
        if (std::abs(m_velocity.x) >= std::abs(m_velocity.y)) {
            // Moving more horizontally, treat as side hit
            resolve_x = true;
        } else {
            // Moving more vertically, treat as top/bottom hit
            resolve_x = false;
        }
    }

    if (resolve_x) {
        if (m_velocity.x > 0.0f) {
            // Ball moving right hit the left side of brick
            m_position.x = brick_bounds.position.x - ball_bounds.size.x;
        } else {
            // Ball moving left hit the right side of brick
            m_position.x = brick_bounds.position.x + brick_bounds.size.x;
        }
        m_velocity.x = -m_velocity.x;
    } else {
        if (m_velocity.y > 0.0f) {
            // Ball moving down hit the top side of brick
            m_position.y = brick_bounds.position.y - ball_bounds.size.y;
        } else {
            // Ball moving up hit the bottom side of brick
            m_position.y = brick_bounds.position.y + brick_bounds.size.y;
        }
        // Reverse vertical velocity
        m_velocity.y = -m_velocity.y;
    }

    m_circle.setPosition(m_position);
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
        m_on_die.emit();
    }

    m_circle.setPosition(sf::Vector2f(m_position));

    // Process collision after position update
    emit_collision_signal();
}

Signal<> &Ball::die_signal() {
    return m_on_die;
}

void Ball::reset() {
    m_position = m_resting_position;
    m_circle.setPosition(m_position);
    m_velocity = sf::Vector2f{0, 0};
    m_is_moving = false;
}

sf::Vector2f Ball::get_velocity() const {
    return m_velocity;
}

void Ball::set_velocity(sf::Vector2f velocity) {
    m_velocity = velocity;
    if (velocity != sf::Vector2f{0, 0}) {
        m_is_moving = true;
    }
}

bool Ball::is_moving() const {
    return m_is_moving;
}

} // namespace pongario
