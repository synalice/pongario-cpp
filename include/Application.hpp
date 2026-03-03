// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Ball.hpp"
#include "CollisionManager.hpp"
#include "GameOverScreen.hpp"
#include "Paddle.hpp"
#include "interface/GameObject.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <vector>

namespace pongario {

class Application {
  public:
    Application();

    void run();

  private:
    int lifes{3};
    bool m_running{true};
    bool m_game_over_pending{false};
    std::unique_ptr<sf::RenderWindow> m_window{nullptr};
    std::vector<std::shared_ptr<GameObject>> m_game_objects{};
    CollisionManager m_collision_manager{};
    std::shared_ptr<Paddle> paddle{};
    std::shared_ptr<Ball> ball{};
    std::shared_ptr<GameOverScreen> game_over_screen{};
    sf::Font m_font{};

    void handle_events();
    void process_physics(float delta);
    void draw();
    void reset();
    void show_game_over_screen();
    sf::Vector2f calculate_ball_resting_position();
};

} // namespace pongario
