// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Hearts.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <utility>
#include <vector>

namespace pongario {

Hearts::Hearts() : m_texture(std::make_shared<sf::Texture>("assets/heart.png")) {
    this->init();
}

void Hearts::init() {
    m_lifes = LIFES;
    m_sprites.clear();

    constexpr float gap = 100.0f;

    for (int i = 0; i < LIFES; i++) {
        sf::Sprite sprite(*m_texture);
        sprite.setScale({11, 11});
        sprite.setPosition({static_cast<float>(i) * gap, 0.0f});
        m_sprites.push_back(std::move(sprite));
    }
}

void Hearts::subtract() {
    m_lifes -= 1;
}

void Hearts::reset() {
    this->init();
}

sf::FloatRect Hearts::get_bounds() const {
    return {};
}

void Hearts::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &sprite : m_sprites) {
        target.draw(sprite, states);
    }
}

} // namespace pongario
