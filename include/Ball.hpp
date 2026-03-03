// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace pongario {

class Ball : public GameObject {
  public:
    explicit Ball(sf::Vector2u window_size);

    void handle_input(float delta);
    void set_window_size(sf::Vector2u window_size);
    sf::FloatRect get_bounds() const override;
    void bounce_vertical(const sf::FloatRect &paddle_bounds);

    Signal<> &wall_bounce_signal();
    Signal<const sf::FloatRect &> &paddle_bounce_signal();

  private:
    sf::CircleShape m_circle{};
    sf::Vector2f m_position{};
    sf::Vector2f m_velocity{};
    sf::Vector2u m_window_size{};
    Signal<> m_on_wall_bounce{};
    Signal<const sf::FloatRect &> m_on_paddle_bounce{};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void process_physics(float delta) override;
};

} // namespace pongario
