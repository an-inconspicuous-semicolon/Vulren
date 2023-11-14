//
// Created by reece on 02/11/2023.
//

#pragma once

#include <type_traits>
#include <exception>

namespace vulren
{
class Resource;

class ResourceHandle;

template <typename T>
requires std::is_base_of_v<Resource, T>
class Handle;
}

#include "Vulren/ResourceManager.hpp"


namespace vulren
{

class Resource
{
public:
    virtual ~Resource() = 0;

protected:
    friend class ResourceManager;

    Resource() = default;
};

class ResourceHandle
{
public:
    ResourceHandle();
    virtual ~ResourceHandle();

    ResourceHandle(const ResourceHandle& other);
    ResourceHandle& operator=(const ResourceHandle& other);

    ResourceHandle(ResourceHandle&& other) noexcept;
    ResourceHandle& operator=(ResourceHandle&& other) noexcept;

    class InvalidAccessException
            : public std::exception
    {
    public:
        const char* what() const noexcept override;
    };

protected:
    friend class ResourceManager;

    ResourceHandle(class ResourceManager* manager, Resource* resource);

protected:
    Resource* m_handle;
    ResourceManager* m_manager;
};

template <typename T>
requires std::is_base_of_v<Resource, T>
class Handle
        : public ResourceHandle
{
public:
    Handle() = default;
    ~Handle() override = default;

    const T* operator->() const
    { return get(); }

    const T* get() const
    {
        return get();
    }

    T* operator->()
    { return get(); }

    T* get()
    {
        if (!m_handle) throw InvalidAccessException();
        return dynamic_cast<T*>(m_handle);
    }

protected:
    friend class ResourceManager;

    Handle(class ResourceManager* manager, T* resource)
            : ResourceHandle(manager, dynamic_cast<Resource*>(resource))
    {
    }
};


} // vulren
