// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "GameObject.hpp"

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
    bool m_running{true};
    std::unique_ptr<sf::RenderWindow> m_window{nullptr};
    std::vector<std::unique_ptr<GameObject>> m_game_objects{};

    void handle_events();
    void process_physics(float delta);
};

} // namespace pongario
