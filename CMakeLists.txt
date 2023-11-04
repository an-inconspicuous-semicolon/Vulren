cmake_minimum_required(VERSION 3.23)

project(Vulren
        DESCRIPTION "A Very Unloved DX12 rendering library"
        VERSION 0.1.0.0
        HOMEPAGE_URL "None yet!"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Libraries/result)
add_subdirectory(Libraries/spdlog)

add_library(Vulren STATIC
        Library/src/Message.cpp
        Library/include/Vulren/Message.hpp
        Library/include/Vulren/vulren.hpp
        Library/src/Result.cpp
        Library/include/Vulren/Result.hpp
        Library/src/Logging.cpp
        Library/src/internal/Logging.hpp
        Library/include/Vulren/Logging.hpp
        Library/src/Instance.cpp
        Library/include/Vulren/Instance.hpp
        Library/src/Resource.cpp
        Library/include/Vulren/Resource.hpp
        Library/src/ResourceManager.cpp
        Library/include/Vulren/ResourceManager.hpp
)
target_include_directories(Vulren
        PUBLIC Library/include
        PRIVATE Library/src/internal
)
target_link_libraries(Vulren
        PUBLIC spdlog Result
        PRIVATE
)


add_executable(VulrenClient Client/main.cpp)
target_include_directories(VulrenClient
        PRIVATE Client
)
target_link_libraries(VulrenClient
        PUBLIC Vulren
)
