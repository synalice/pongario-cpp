// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace pongario {

class Ball : public GameObject {
  public:
    static constexpr float RADIUS = 50.0f;

    explicit Ball(sf::Vector2f resting_position);

    void handle_input(float delta);
    void set_window_size(sf::Vector2u window_size);
    void bounce_vertical(const sf::FloatRect &paddle_bounds);
    void bounce_brick(const sf::FloatRect &brick_bounds);
    void reset();
    void set_velocity(sf::Vector2f velocity);
    bool is_moving() const;
    sf::FloatRect get_bounds() const override;
    Signal<> &die_signal();
    sf::Vector2f get_velocity() const;

  private:
    bool m_is_moving{};
    sf::CircleShape m_circle{};
    sf::Vector2f m_position{};
    sf::Vector2f m_velocity{};
    sf::Vector2f m_resting_position{};
    sf::Vector2u m_window_size{};
    Signal<> m_on_die{};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void process_physics(float delta) override;
};

} // namespace pongario
