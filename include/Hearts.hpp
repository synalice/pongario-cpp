// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace pongario {

class Hearts : public GameObject {
    static constexpr int LIFES = 3;

  public:
    explicit Hearts();

    sf::FloatRect get_bounds() const override;
    void subtract();
    void restart();
    int get_lifes();

  private:
    int m_lifes{LIFES};
    std::shared_ptr<sf::Texture> m_texture{};
    std::vector<sf::Sprite> m_sprites;

    void init();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

} // namespace pongario
