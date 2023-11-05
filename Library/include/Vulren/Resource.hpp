//
// Created by reece on 02/11/2023.
//

#pragma once

#include <type_traits>

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
    virtual ~ResourceHandle();

    ResourceHandle(const ResourceHandle& other);
    ResourceHandle& operator=(const ResourceHandle& other) = delete;

protected:
    friend class ResourceManager;

    ResourceHandle(class ResourceManager& manager, Resource* resource);

protected:
    Resource* m_handle;
    ResourceManager& m_manager;
};

template <typename T>
requires std::is_base_of_v<Resource, T>
class Handle
        : public ResourceHandle
{
public:
    ~Handle() override = default;

    const T* operator->() const
    { return get(); }

    const T* get() const
    { return dynamic_cast<T*>(m_handle); }

    T* operator->()
    { return get(); }

    T* get()
    { return dynamic_cast<T*>(m_handle); }

protected:
    friend class ResourceManager;

    Handle(class ResourceManager& manager, T* resource)
            : ResourceHandle(manager, dynamic_cast<Resource*>(resource))
    {
    }
};


} // vulren
