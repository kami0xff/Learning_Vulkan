cmake_minimum_required(VERSION 3.21)
project(LearningVulkan)

set(CMAKE_CXX_STANDARD 20)
find_package(Vulkan)
find_package(glfw3)
add_executable(LearningVulkan main.cpp VkApp.cpp VkApp.h)
target_link_libraries(LearningVulkan vulkan glfw)
