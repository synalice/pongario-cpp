// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "interface/GameObject.hpp"

#include <memory>
#include <vector>

namespace pongario {

class Ball;
class Paddle;

class CollisionManager {
  public:
    void check_collisions(const std::vector<std::unique_ptr<GameObject>> &objects);

  private:
    void handle_ball_paddle_collision(Ball &ball, const Paddle &paddle);
};

} // namespace pongario
