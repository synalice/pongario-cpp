// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Ball.hpp"
#include "CollisionManager.hpp"
#include "GameOverScreen.hpp"
#include "Hearts.hpp"
#include "Paddle.hpp"
#include "YouWinScreen.hpp"
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
    bool m_running{true};
    bool m_game_over_screen_pending{false};
    bool m_game_over_screen_shown{false};
    bool m_you_win_screen_pending{false};
    bool m_you_win_screen_shown{false};
    CollisionManager m_collision_manager{};
    std::unique_ptr<sf::RenderWindow> m_window{nullptr};
    std::vector<std::shared_ptr<GameObject>> m_game_objects{};
    std::shared_ptr<Paddle> m_paddle{};
    std::shared_ptr<Ball> m_ball{};
    std::shared_ptr<GameOverScreen> m_game_over_screen{};
    std::shared_ptr<YouWinScreen> m_you_win_screen{};
    std::shared_ptr<Hearts> m_hearts{};
    sf::Font m_font{};

    void handle_events();
    void process_physics(float delta);
    void draw();
    void reset();
    void show_game_over_screen();
    void show_you_win_screen();
    void restart_game();
    sf::Vector2f calculate_ball_resting_position();
};

} // namespace pongario
