//
// Created by reece on 08/11/2023.
//

#pragma once

namespace vulren
{

template <typename T>
class Wrapper
{
public:
    virtual ~Wrapper() = default;

    operator T() // NOLINT(google-explicit-constructor)
    { return get(); };

    virtual T get() = 0;
};

}