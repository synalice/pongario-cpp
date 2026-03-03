// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"
#include "interface/Signal.hpp"

#include <memory>
#include <unordered_set>
#include <vector>

namespace pongario {

class CollisionManager {
  public:
    CollisionManager();
    ~CollisionManager();

    // Rule of 5: Since we have a custom destructor, we need to define copy/move operations
    CollisionManager(const CollisionManager &) = delete;
    CollisionManager &operator=(const CollisionManager &) = delete;
    CollisionManager(CollisionManager &&) = default;
    CollisionManager &operator=(CollisionManager &&) = default;

    void register_game_object(std::shared_ptr<GameObject> object);
    void unregister_game_object(std::shared_ptr<GameObject> object);

  private:
    void on_collision_signal(GameObject &object, const sf::FloatRect &bounds);
    void check_collision_with_others(GameObject &source, const sf::FloatRect &source_bounds);

    std::vector<std::shared_ptr<GameObject>> m_registered_objects{};
    std::unordered_set<Signal<GameObject &, const sf::FloatRect &>::ConnectionId> m_connections{};
};

} // namespace pongario
