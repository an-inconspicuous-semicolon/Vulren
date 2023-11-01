cmake_minimum_required(VERSION 3.23)

project(Vulren
        DESCRIPTION "A Very Unloved DX12 rendering library"
        VERSION 0.1.0.0
        HOMEPAGE_URL "None yet!"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Vulren STATIC)
target_sources(Vulren PUBLIC Library/include/Vulren/vulren.h Library/src/vulren.cpp)
target_include_directories(Vulren
        PUBLIC Library/include
        PRIVATE Library/src/private
)
target_link_libraries(Vulren
        PUBLIC
        PRIVATE
)

add_executable(Client)
target_sources(Client PUBLIC Client/main.cpp)
target_include_directories(Client
        PRIVATE Client
)
target_link_libraries(Client
        PUBLIC Vulren
)