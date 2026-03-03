// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

#include <iostream>
#include <memory>
#include <utility>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

namespace pongario {

Application::Application()
    : m_window(std::make_unique<sf::RenderWindow>(
          sf::VideoMode({200, 200}),
          "Pongario",
          sf::Style::None,
          sf::State::Fullscreen)) {
    m_game_objects.push_back(std::make_unique<Paddle>(m_window->getSize()));

    auto ball = std::make_unique<Ball>(m_window->getSize());

    ball->wall_bounce_signal().connect([]() {
        std::cout << "Ball bounced off wall!" << std::endl;
    });

    ball->paddle_bounce_signal().connect([](const sf::FloatRect &paddle_bounds) {
        std::cout << "Ball hit paddle at position: ("
                  << paddle_bounds.position.x << ", "
                  << paddle_bounds.position.y << ")" << std::endl;
    });

    m_game_objects.push_back(std::move(ball));

    // Register all game objects with the collision manager
    for (auto &game_object : m_game_objects) {
        m_collision_manager.register_game_object(*game_object);
    }
}

void Application::run() {
    sf::Clock clock;

    while (m_running && m_window->isOpen()) {
        this->handle_events();

        const float delta = clock.restart().asSeconds();
        this->process_physics(delta);

        this->draw();
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

void Application::draw() {
    m_window->clear(sf::Color::White);
    for (const auto &game_object : m_game_objects) {
        m_window->draw(*game_object);
    }
    m_window->display();
}

} // namespace pongario
