//
// Created by reece on 02/11/2023.
//

#include <stdexcept>
#include <algorithm>
#include "Vulren/ResourceManager.hpp"
#include "internal/Logging.hpp"

namespace vulren
{

unsigned int ResourceManager::s_total_number_of_resources = 0;
unsigned int ResourceManager::s_total_number_of_references = 0;

ResourceManager::ResourceManager()
= default;

ResourceManager::~ResourceManager()
= default;

void ResourceManager::add_reference(Resource* resource)
{
    if (!m_resource_counts.contains(resource))
    {
        m_resource_counts.insert({resource, 1});
        internal::log_info("registered resource");
        m_total_number_of_resources++;
        s_total_number_of_resources++;
        m_total_number_of_references++;
        s_total_number_of_references++;
    } else
    {
        m_resource_counts.at(resource)++;
        internal::log_info("Added reference to resource");
        m_total_number_of_references++;
        s_total_number_of_references++;
    }
}

void ResourceManager::remove_reference(Resource* resource)
{
    if (!m_resource_counts.contains(resource))
    {
        // something funky happened
        throw std::invalid_argument("Invalid resource pointer");
    } else
    {
        unsigned int count = --m_resource_counts.at(resource);
        internal::log_info("removed reference from resource");
        if (count == 0)
        {
            m_resource_counts.erase(resource);
            auto it = std::find(m_resources.begin(), m_resources.end(), resource);
            m_resources.erase(it);
            internal::log_info("deleted resource");
        }
    }
}

} // vulren