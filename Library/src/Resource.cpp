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
    m_manager.remove_reference(m_handle);
}

ResourceHandle::ResourceHandle(struct ResourceManager& manager, Resource* resource)
        : m_manager(manager),
          m_handle(resource)
{
    m_manager.add_reference(m_handle);
}

ResourceHandle::ResourceHandle(const ResourceHandle& other)
        : m_manager(other.m_manager),
          m_handle(other.m_handle)
{
    m_manager.add_reference(m_handle);
}

} // vulren