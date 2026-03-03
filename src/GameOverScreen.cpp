// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "GameOverScreen.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace pongario {

GameOverScreen::GameOverScreen(const sf::Font &font) : m_text(font) {
    m_text.setString("Game Over!");
    m_text.setCharacterSize(72);
    m_text.setFillColor(sf::Color::Red);

    // Get screen dimensions and center the text
    const sf::Vector2u screen_size = sf::VideoMode::getDesktopMode().size; // TODO: Replace all window_size in constructurs with this
    const sf::Vector2f m_screen_center = sf::Vector2f(static_cast<float>(screen_size.x) / 2.0f, static_cast<float>(screen_size.y) / 2.0f);

    // Center the text origin
    const sf::FloatRect text_bounds = m_text.getLocalBounds();
    m_text.setOrigin(text_bounds.getCenter());

    m_text.setPosition(m_screen_center);
}

void GameOverScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_text, states);
}

sf::FloatRect GameOverScreen::get_bounds() const {
    return m_text.getGlobalBounds();
}

void GameOverScreen::process_physics(float delta) {
    // GameOverScreen doesn't need physics processing
    (void)delta;
}

} // namespace pongario
