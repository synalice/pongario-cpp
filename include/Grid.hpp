// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Brick.hpp"
#include "interface/GameObject.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>
#include <memory>
#include <vector>

namespace pongario {

struct GridConfig {
    sf::Vector2u window_size;
    size_t rows;
    size_t columns;
    float brick_width;
    float brick_height;
    float horizontal_gap;
    float vertical_gap;
};

class Grid : public GameObject {
  public:
    explicit Grid(const GridConfig &config);

    const std::vector<std::shared_ptr<Brick>> &get_bricks() const;
    sf::FloatRect get_bounds() const override;
    int bricks_left();
    Signal<Brick &> &brick_destroyed_signal();

  private:
    std::vector<std::shared_ptr<Brick>> m_bricks{};
    sf::Vector2u m_window_size{};
    GridConfig m_grid_config{};
    int m_bricks_created{};
    int m_bricks_destroyed{};
    Signal<Brick &> m_on_brick_destroyed{};

    void generate_bricks();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void process_physics(float delta) override;
};

} // namespace pongario
