//
// Created by reece on 02/11/2023.
//

#include "Vulren/Resource.hpp"
#include "Vulren/ResourceManager.hpp"

namespace vulren
{

Resource::~Resource()
= default;

ResourceHandle::~ResourceHandle()
{
    if (!m_handle) return;
    m_manager->remove_reference(m_handle);
}

ResourceHandle::ResourceHandle(struct ResourceManager* manager, Resource* resource)
        : m_manager(manager),
          m_handle(resource)
{
    m_manager->add_reference(m_handle);
}

ResourceHandle::ResourceHandle(const ResourceHandle& other)
        : m_manager(other.m_manager),
          m_handle(other.m_handle)
{
    ;
    m_manager->add_reference(m_handle);
}

ResourceHandle::ResourceHandle()
        : m_manager(nullptr),
          m_handle(nullptr)
{
}

ResourceHandle& ResourceHandle::operator=(const ResourceHandle& other)
{
    if (this == &other) return *this;

    m_handle = other.m_handle;
    m_manager = other.m_manager;
    m_manager->add_reference(m_handle);

    return *this;
}

ResourceHandle::ResourceHandle(ResourceHandle&& other) noexcept
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;

    m_manager = other.m_manager;
}

ResourceHandle& ResourceHandle::operator=(ResourceHandle&& other) noexcept
{
    if (this == &other) return *this;

    m_handle = other.m_handle;
    other.m_handle = nullptr;

    m_manager = other.m_manager;

    return *this;
}

const char* ResourceHandle::InvalidAccessException::what() const noexcept
{
    return "Attempted to access the pointer of an uninitialised handle";
}
} // vulren