// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

namespace pongario {

class PhysicsProcessor {
  public:
    virtual ~PhysicsProcessor() = default;
    virtual void process_physics(float delta) {}
};

} // namespace pongario
