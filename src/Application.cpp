// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.hpp"
#include "Ball.hpp"
#include "Grid.hpp"
#include "Paddle.hpp"

#include <memory>
#include <utility>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

namespace pongario {

Application::Application()
    : m_window(std::make_unique<sf::RenderWindow>(
          sf::VideoMode::getDesktopMode(),
          "Pongario",
          sf::Style::None,
          sf::State::Fullscreen)),
      paddle(std::make_shared<Paddle>(m_window->getSize())),
      ball(std::make_shared<Ball>(m_window->getSize())) {
    ball->die_signal().connect([this]() {
        lifes -= 1;
        this->reset();
        if (lifes == 0) {
            m_running = false;
        }
    });

    m_game_objects.push_back(ball);
    m_game_objects.push_back(paddle);

    const GridConfig grid_config{
        .window_size = m_window->getSize(),
        .rows = 5,
        .columns = 8,
        .brick_width = 250.0f,
        .brick_height = 100.0f,
        .horizontal_gap = 90.0f,
        .vertical_gap = 100.0f};

    auto grid = std::make_unique<Grid>(grid_config);

    // Register each brick individually with the collision manager
    for (auto brick_ref : grid->get_bricks()) {
        m_collision_manager.register_game_object(brick_ref.get());
    }

    m_game_objects.push_back(std::move(grid));

    // Register paddle and ball with the collision manager
    for (auto &game_object : m_game_objects) {
        // Skip Grid itself - only its bricks are registered
        if (dynamic_cast<Grid *>(game_object.get()) == nullptr) {
            m_collision_manager.register_game_object(*game_object);
        }
    }

    this->reset();
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

void Application::reset() {
    paddle->reset();

    const sf::FloatRect paddle_bounds = paddle->get_bounds();

    sf::Vector2f ball_reset_position{};
    ball_reset_position.x = paddle_bounds.position.x + (paddle_bounds.size.x / 2.0f) - Ball::RADIUS;
    ball_reset_position.y = paddle_bounds.position.y - (2.0f * Ball::RADIUS);

    if (ball_reset_position.y < 0.0f) {
        ball_reset_position.y = 0.0f;
    }

    ball->set_reset_position(ball_reset_position);
    ball->reset();
}

} // namespace pongario
