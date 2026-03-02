// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.hpp"

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

namespace pongario {

Application::Application()
    : m_window(std::make_unique<sf::RenderWindow>(
          sf::VideoMode({200, 200}),
          "SFML works!",
          sf::Style::None,
          sf::State::Fullscreen)) {}

void Application::run() {
    sf::Clock clock;

    while (m_running && m_window->isOpen()) {
        this->handle_events();

        // Get elapsed time
        const float delta = clock.restart().asSeconds();
        this->process_physics(delta);

        m_window->clear();
        // window.draw(sprite);
        m_window->display();
    }

    m_window->close();
}

void Application::handle_events() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
        m_running = false;
    }
}

void Application::process_physics(float delta) {
}

} // namespace pongario
