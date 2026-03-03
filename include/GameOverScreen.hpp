// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace pongario {

class GameOverScreen : public GameObject {
  public:
    explicit GameOverScreen(const sf::Font &font);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::FloatRect get_bounds() const override;
    void process_physics(float delta) override;

  private:
    sf::Text m_text;
};

} // namespace pongario
