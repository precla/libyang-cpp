/*
 * Copyright (C) 2021 CESNET, https://photonics.cesnet.cz/
 *
 * Written by Václav Kubernát <kubernat@cesnet.cz>
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include <libyang/libyang.h>
#include <libyang-cpp/utils/exception.hpp>
#include <libyang-cpp/Module.hpp>

namespace libyang {
Module::Module(const lys_module* module, std::shared_ptr<ly_ctx> ctx)
    : m_ctx(ctx)
    , m_module(module)
{
}

/**
 * Returns the name of the module.
 */
std::string_view Module::name() const
{
    return m_module->name;
}

/**
 * Returns whether feature is enabled. Throws if the feature doesn't exist.
 */
bool Module::featureEnabled(const char* featureName) const
{
    using namespace std::string_literals;
    auto ret = lys_feature_value(m_module, featureName);
    switch (ret) {
    case LY_SUCCESS:
        return true;
    case LY_ENOT:
        return false;
    case LY_ENOTFOUND:
        throw ErrorWithCode("Feature '"s + featureName + "' doesn't exist within module '" + std::string(name()) + "'", ret);
    default:
        throw ErrorWithCode("Error while enabling feature (" + std::to_string(ret) + ")", ret);
    }
}
}
