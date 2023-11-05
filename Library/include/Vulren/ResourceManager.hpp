//
// Created by reece on 02/11/2023.
//

#pragma once

#include <unordered_map>
#include <vector>

#include "Vulren/Resource.hpp"

namespace vulren
{

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

protected:
    friend class vulren::ResourceHandle;

    void add_reference(Resource* resource);
    void remove_reference(Resource* resource);

    template <typename T>
    Handle<T> create_handle(T* resource)
    {
        return Handle(*this, resource);
    }

protected:
    std::unordered_map<Resource*, unsigned int> m_resource_counts;
    std::vector<Resource*> m_resources;

private:
    unsigned int m_total_number_of_resources = 0;
    unsigned int m_total_number_of_references = 0;
    static unsigned int s_total_number_of_resources;
    static unsigned int s_total_number_of_references;

};

} // vulren
