// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

namespace pongario {

class Application {
  public:
    Application();

    void run();

  private:
    bool m_running{true};
    std::unique_ptr<sf::RenderWindow> m_window;

    void handle_events();
    void process_physics(float delta);
};

} // namespace pongario
