// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"
#include "interface/Signal.hpp"

#include <unordered_set>
#include <vector>

namespace pongario {

class CollisionManager {
  public:
    CollisionManager();
    ~CollisionManager();

    void register_game_object(GameObject &object);
    void unregister_game_object(GameObject &object);

  private:
    void on_collision_signal(GameObject &object, const sf::FloatRect &bounds);
    void check_collision_with_others(GameObject &source, const sf::FloatRect &source_bounds);

    std::vector<GameObject *> m_registered_objects{};
    std::unordered_set<Signal<GameObject &, const sf::FloatRect &>::ConnectionId> m_connections{};
};

} // namespace pongario
