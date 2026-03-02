// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

namespace pongario {

class PhysicsProcessor {
  public:
    virtual void process_physics(float delta) = 0;
};

} // namespace pongario
