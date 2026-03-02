// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "CollisionManager.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "interface/GameObject.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <memory>
#include <vector>

namespace pongario {

void CollisionManager::check_collisions(const std::vector<std::unique_ptr<GameObject>> &objects) {
    Ball *ball = nullptr;
    Paddle const *paddle = nullptr;

    for (const auto &obj : objects) {
        if (auto *b = dynamic_cast<Ball *>(obj.get())) {
            ball = b;
        } else if (auto *p = dynamic_cast<Paddle *>(obj.get())) {
            paddle = p;
        }
    }

    if (ball != nullptr && paddle != nullptr) {
        handle_ball_paddle_collision(*ball, *paddle);
    }
}

void CollisionManager::handle_ball_paddle_collision(Ball &ball, const Paddle &paddle) {
    const sf::FloatRect ball_bounds = ball.get_bounds();
    const sf::FloatRect paddle_bounds = paddle.get_bounds();

    if (ball_bounds.findIntersection(paddle_bounds).has_value()) {
        ball.bounce_vertical(paddle_bounds.position.y);
    }
}

} // namespace pongario
