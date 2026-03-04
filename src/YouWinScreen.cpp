// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "YouWinScreen.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace pongario {

YouWinScreen::YouWinScreen(const sf::Font &font)
    : m_text_you_win(font),
      m_text_press_to_restart(font) {
    // Get screen dimensions and center the text
    const sf::Vector2u screen_size = sf::VideoMode::getDesktopMode().size;
    const sf::Vector2f m_screen_center = sf::Vector2f(static_cast<float>(screen_size.x) / 2.0f, static_cast<float>(screen_size.y) / 2.0f);

    m_text_you_win.setString("You Win!");
    m_text_you_win.setCharacterSize(130);
    m_text_you_win.setFillColor(sf::Color::Black);

    const sf::FloatRect text_bounds = m_text_you_win.getLocalBounds();
    m_text_you_win.setOrigin(text_bounds.getCenter());
    m_text_you_win.setPosition(m_screen_center);

    m_text_press_to_restart.setString("Press Space to restart");
    m_text_press_to_restart.setCharacterSize(70);
    m_text_press_to_restart.setFillColor(sf::Color::Black);

    const sf::FloatRect text_bounds_2 = m_text_press_to_restart.getLocalBounds();
    m_text_press_to_restart.setOrigin(text_bounds_2.getCenter());
    m_text_press_to_restart.setPosition(m_screen_center - sf::Vector2f{0.0f, -170.0f});
}

void YouWinScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_text_you_win, states);
    target.draw(m_text_press_to_restart, states);
}

sf::FloatRect YouWinScreen::get_bounds() const {
    return m_text_you_win.getGlobalBounds();
}

} // namespace pongario
