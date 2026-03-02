// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include "Brick.hpp"
#include "interface/GameObject.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>
#include <functional>
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

    std::vector<std::reference_wrapper<Brick>> get_bricks();
    sf::FloatRect get_bounds() const override;

  private:
    std::vector<std::unique_ptr<Brick>> m_bricks{};
    sf::Vector2u m_window_size{};
    GridConfig m_grid_config{};

    void generate_bricks();
    sf::Color get_color_for_row(size_t row) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void process_physics(float delta) override;
};

} // namespace pongario
