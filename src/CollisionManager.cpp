// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "CollisionManager.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>

namespace pongario {

CollisionManager::CollisionManager() = default;

CollisionManager::~CollisionManager() {
    for (auto *object : m_registered_objects) {
        if (object) {
            object->collision_signal().disconnect(0);
        }
    }
}

void CollisionManager::register_game_object(GameObject &object) {
    m_registered_objects.push_back(&object);
    auto connection_id = object.collision_signal().connect(
        [this](GameObject &obj, const sf::FloatRect &bounds) {
            on_collision_signal(obj, bounds);
        });
    m_connections.insert(connection_id);
}

void CollisionManager::unregister_game_object(GameObject &object) {
    auto it = std::find(m_registered_objects.begin(), m_registered_objects.end(), &object);
    if (it != m_registered_objects.end()) {
        m_registered_objects.erase(it);
    }
}

void CollisionManager::on_collision_signal(GameObject &source, const sf::FloatRect &source_bounds) {
    for (auto *other : m_registered_objects) {
        if (other == &source)
            continue;

        const sf::FloatRect other_bounds = other->get_bounds();
        if (source_bounds.findIntersection(other_bounds).has_value()) {
            auto *ball = dynamic_cast<Ball *>(&source);
            const auto *paddle = dynamic_cast<const Paddle *>(other);
            auto *brick = dynamic_cast<Brick *>(other);

            if (ball && paddle) {
                ball->bounce_vertical(other_bounds);
                ball->paddle_bounce_signal().emit(other_bounds);
            } else if (ball && brick && !brick->is_destroyed()) {
                ball->bounce_brick(other_bounds);
                ball->brick_bounce_signal().emit(other_bounds);
                brick->mark_destroyed();
            } else {
                ball = dynamic_cast<Ball *>(other);
                paddle = dynamic_cast<const Paddle *>(&source);
                brick = dynamic_cast<Brick *>(&source);

                if (ball && paddle) {
                    ball->bounce_vertical(source_bounds);
                    ball->paddle_bounce_signal().emit(source_bounds);
                } else if (ball && brick && !brick->is_destroyed()) {
                    ball->bounce_brick(source_bounds);
                    ball->brick_bounce_signal().emit(source_bounds);
                    brick->mark_destroyed();
                }
            }
        }
    }
}
} // namespace pongario
