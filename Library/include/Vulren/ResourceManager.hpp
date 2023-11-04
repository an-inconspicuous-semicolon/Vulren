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

private:
    std::unordered_map<Resource*, unsigned int> m_resource_counts;
    std::vector<Resource*> m_resources;
};

} // vulren
