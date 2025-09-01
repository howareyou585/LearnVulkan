cmake_minimum_required(VERSION 3.30)
project(j_test LANGUAGES CXX VERSION 1.0.0)
add_library(cxx_std INTERFACE)
target_compile_features(cxx_std INTERFACE cxx_std_20)

add_executable(vulkan_test test.cpp)
target_include_directories(vulkan_test PUBLIC "glfw/include")
target_link_directories(vulkan_test PUBLIC "glfw/lib")
target_link_libraries(vulkan_test PUBLIC cxx_std glfw3 vulkan-1)