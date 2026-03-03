// SPDX-FileCopyrightText: 2026 Nikita Krasnov <nikita.nikita.krasnov@gmail.com>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace pongario {

template <typename... Args>
class Signal {
  public:
    using Callback = std::function<void(Args...)>;
    using ConnectionId = size_t;

    ConnectionId connect(Callback callback) {
        const ConnectionId id = m_next_id++;
        m_callbacks.emplace_back(id, std::move(callback));
        return id;
    }

    void disconnect(ConnectionId id) {
        m_callbacks.erase(
            std::remove_if(m_callbacks.begin(),
                           m_callbacks.end(),
                           [id](const auto &pair) { return pair.first == id; }),
            m_callbacks.end());
    }

    void emit(Args... args) const {
        for (const auto &[id, callback] : m_callbacks) {
            callback(args...);
        }
    }

  private:
    std::vector<std::pair<ConnectionId, Callback>> m_callbacks{};
    ConnectionId m_next_id{0};
};

} // namespace pongario
