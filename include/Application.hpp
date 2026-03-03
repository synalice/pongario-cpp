// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Ball.hpp"
#include "CollisionManager.hpp"
#include "Paddle.hpp"
#include "interface/GameObject.hpp"

#include <SFML/Graphics/Drawable.hpp>
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
    std::unique_ptr<sf::RenderWindow> m_window{nullptr};
    std::vector<std::shared_ptr<GameObject>> m_game_objects{};
    CollisionManager m_collision_manager{};
    std::shared_ptr<Ball> ball{};
    std::shared_ptr<Paddle> paddle{};

    void handle_events();
    void process_physics(float delta);
    void draw();
};

} // namespace pongario
