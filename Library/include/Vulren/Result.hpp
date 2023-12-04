//
// Created by reece on 01/11/2023.
//

#pragma once

#include <result.hpp>
#include "Vulren/Message.hpp"


namespace vulren
{
template <typename T>
using Result = cpp::result<T, Message*>;
}