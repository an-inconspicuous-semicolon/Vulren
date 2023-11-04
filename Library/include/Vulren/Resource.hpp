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

class DummyResource
        : public Resource
{
public:
    DummyResource() = default;
    ~DummyResource() override = default;
};

class ResourceHandle
{
public:
    virtual ~ResourceHandle();

    ResourceHandle(const ResourceHandle& other);
    ResourceHandle& operator=(const ResourceHandle& other) = delete;

    virtual const Resource* operator->() const
    { return get(); }

    virtual const Resource* get() const
    { return m_handle; }

    virtual Resource* operator->()
    { return get(); }

    virtual Resource* get()
    { return m_handle; }

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

    const T* operator->() const override
    { return get(); }

    const T* get() const override
    { return dynamic_cast<T*>(m_handle); }

    T* operator->() override
    { return get(); }

    T* get() override
    { return dynamic_cast<T*>(m_handle); }

protected:
    friend class ResourceManager;

    Handle(class ResourceManager& manager, T* resource)
            : ResourceHandle(manager, dynamic_cast<Resource*>(resource))
    {
    }
};


} // vulren
