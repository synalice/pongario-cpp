// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace pongario {

class Paddle : public GameObject {
  public:
    explicit Paddle(sf::Vector2u window_size);

    void handle_input(float delta);
    void set_window_size(sf::Vector2u window_size);
    void reset();
    sf::FloatRect get_bounds() const override;
    sf::Vector2f get_position() const;
    Signal<> &moved_left_signal();
    Signal<> &moved_right_signal();

  private:
    sf::RectangleShape m_rectangle{};
    sf::Vector2f m_position{};
    sf::Vector2u m_window_size{};
    Signal<> m_on_moved_left{};
    Signal<> m_on_moved_right{};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void process_physics(float delta) override;
};

} // namespace pongario
