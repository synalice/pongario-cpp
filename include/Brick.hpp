// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"
#include "interface/Signal.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace pongario {

struct BrickConfig {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
};

class Brick : public GameObject {
  public:
    explicit Brick(const BrickConfig &config);

    void mark_destroyed();
    bool is_destroyed() const;
    sf::FloatRect get_bounds() const override;

    Signal<Brick &> &destroyed_signal();

  private:
    sf::RectangleShape m_rectangle{};
    sf::Vector2f m_position{};
    bool m_destroyed{false};
    Signal<Brick &> m_on_destroyed{};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

} // namespace pongario
