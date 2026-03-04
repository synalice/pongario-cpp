// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace pongario {

class YouWinScreen : public GameObject {
  public:
    explicit YouWinScreen(const sf::Font &font);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::FloatRect get_bounds() const override;

  private:
    sf::Text m_text_you_win;
    sf::Text m_text_press_to_restart;
};

} // namespace pongario
