/*
 * Copyright (C) 2021 CESNET, https://photonics.cesnet.cz/
 *
 * Written by Václav Kubernát <kubernat@cesnet.cz>
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/
#include <memory>

namespace libyang {
/**
 * @brief A container for strings created by libyang.
 */
class String {
public:
    explicit String(char* str);
    std::shared_ptr<char> get();

    explicit operator std::string();

    bool operator==(const char*) const;
    bool operator==(const std::string_view& str) const;

private:
    std::shared_ptr<char> m_ptr;
};
}