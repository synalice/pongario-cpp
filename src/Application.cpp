// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

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
          sf::State::Fullscreen)) {
    m_game_objects.push_back(std::make_unique<Paddle>(m_window->getSize()));
    m_game_objects.push_back(std::make_unique<Ball>(m_window->getSize()));
}

void Application::run() {
    sf::Clock clock;

    while (m_running && m_window->isOpen()) {
        this->handle_events();

        // Get elapsed time
        const float delta = clock.restart().asSeconds();
        this->process_physics(delta);

        m_window->clear();
        for (const auto &game_object : m_game_objects) {
            m_window->draw(*game_object);
        }
        m_window->display();
    }

    m_window->close();
}

void Application::handle_events() {
    while (const auto event = m_window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_running = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
            m_running = false;
        }
    }
}

void Application::process_physics(float delta) {
    for (const auto &game_object : m_game_objects) {
        game_object->process_physics(delta);
    }
}

} // namespace pongario
