// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.hpp"
#include "Ball.hpp"
#include "GameOverScreen.hpp"
#include "Grid.hpp"
#include "Hearts.hpp"
#include "Paddle.hpp"

#include <memory>
#include <stdexcept>
#include <utility>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
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
      paddle(std::make_shared<Paddle>()),
      hearts(std::make_shared<Hearts>()) {
    if (!m_font.openFromFile("assets/GentiumBookPlus-Regular.ttf")) {
        // Handle font loading error
        throw std::runtime_error("Failed to load font");
    }

    game_over_screen = std::make_shared<GameOverScreen>(m_font);

    ball = std::make_shared<Ball>(this->calculate_ball_resting_position());

    ball->die_signal().connect([this]() {
        lifes -= 1;
        hearts->subtract();
        this->reset();
        if (lifes == 0) {
            m_game_over_pending = true;
        }
    });

    paddle->moved_left_signal().connect([this]() {
        if (!ball->is_moving()) {
            ball->set_velocity(sf::Vector2f{-100, -1000});
        }
    });

    paddle->moved_right_signal().connect([this]() {
        if (!ball->is_moving()) {
            ball->set_velocity(sf::Vector2f{100, -1000});
        }
    });

    m_game_objects.push_back(ball);
    m_game_objects.push_back(paddle);
    m_game_objects.push_back(hearts);

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
    for (auto brick : grid->get_bricks()) {
        m_collision_manager.register_game_object(brick);
    }

    m_game_objects.push_back(std::move(grid));

    // Register paddle and ball with the collision manager
    for (auto &game_object : m_game_objects) {
        // Skip Grid itself - only its bricks are registered
        if (dynamic_cast<Grid *>(game_object.get()) == nullptr) {
            m_collision_manager.register_game_object(game_object);
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

    if (m_game_over_pending) {
        m_game_over_pending = false;
        this->show_game_over_screen();
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
    for (const auto &game_object : m_game_objects) {
        game_object->reset();
    }
}

sf::Vector2f Application::calculate_ball_resting_position() {
    const sf::FloatRect paddle_bounds = paddle->get_bounds();

    sf::Vector2f ball_resting_position{};
    ball_resting_position.x = paddle_bounds.position.x + (paddle_bounds.size.x / 2.0f) - Ball::RADIUS;
    ball_resting_position.y = paddle_bounds.position.y - (2.0f * Ball::RADIUS);

    if (ball_resting_position.y < 0.0f) {
        ball_resting_position.y = 0.0f;
    }
    return ball_resting_position;
}

void Application::show_game_over_screen() {
    if (game_over_screen) {
        m_game_objects.clear();
        m_game_objects.push_back(game_over_screen);
    }
}

} // namespace pongario
