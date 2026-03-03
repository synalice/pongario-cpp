// SPDX-FileCopyrightText: © 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Grid.hpp"
#include "Brick.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <memory>
#include <vector>

namespace pongario {

Grid::Grid(const GridConfig &config)
    : m_window_size(config.window_size), m_grid_config(config) {
    generate_bricks();
}

void Grid::generate_bricks() {
    auto texture = std::make_shared<sf::Texture>("assets/block_brown.png");

    const float total_grid_width = static_cast<float>(m_grid_config.columns) * m_grid_config.brick_width +
                                   static_cast<float>(m_grid_config.columns - 1) * m_grid_config.horizontal_gap;

    const float start_x = (static_cast<float>(m_window_size.x) - total_grid_width) / 2.0f;
    const float start_y = static_cast<float>(m_window_size.y) * 0.15f;

    for (size_t row = 0; row < m_grid_config.rows; ++row) {
        for (size_t col = 0; col < m_grid_config.columns; ++col) {
            const float x = start_x + static_cast<float>(col) * (m_grid_config.brick_width + m_grid_config.horizontal_gap);
            const float y = start_y + static_cast<float>(row) * (m_grid_config.brick_height + m_grid_config.vertical_gap);

            const BrickConfig config{
                .position = sf::Vector2f(x, y),
                .scale = {6, 6},
                .texture = texture,
            };

            m_bricks.push_back(std::make_unique<Brick>(config));
        }
    }
}

std::vector<std::reference_wrapper<Brick>> Grid::get_bricks() {
    std::vector<std::reference_wrapper<Brick>> brick_refs;
    brick_refs.reserve(m_bricks.size());
    std::transform(m_bricks.begin(), m_bricks.end(), std::back_inserter(brick_refs),
                   [](std::unique_ptr<Brick> &brick) { return std::ref(*brick); });
    return brick_refs;
}

sf::FloatRect Grid::get_bounds() const {
    return sf::FloatRect();
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &brick : m_bricks) {
        target.draw(*brick, states);
    }
}

void Grid::process_physics(float delta) {}

} // namespace pongario
