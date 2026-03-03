// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace pongario {

class Paddle : public GameObject {
  public:
    explicit Paddle();

    void handle_input(float delta);
    void set_window_size(sf::Vector2u window_size);
    void reset();
    sf::FloatRect get_bounds() const override;
    sf::Vector2f get_position() const;
    Signal<> &moved_left_signal();
    Signal<> &moved_right_signal();

  private:
    sf::Vector2f m_position{};
    sf::Vector2u m_window_size{};
    Signal<> m_on_moved_left{};
    Signal<> m_on_moved_right{};
    sf::Texture m_texture{};
    sf::Sprite m_sprite;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void process_physics(float delta) override;
};

} // namespace pongario
