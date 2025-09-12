cmake_minimum_required(VERSION 3.30)
#project(learn_Vulkan LANGUAGES CXX VERSION 1.0.0)
#project(j_test LANGUAGES CXX VERSION 1.0.0)


#add_executable(vulkan_test test.cpp)
#target_include_directories(vulkan_test PUBLIC "glfw/include")
#target_link_directories(vulkan_test PUBLIC "glfw/lib")
#target_link_libraries(vulkan_test PUBLIC cxx_std glfw3 vulkan-1)


project(learn_Vulkan LANGUAGES CXX VERSION 1.0.0)
#设置c++ 标准
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(cxx_std INTERFACE)
target_compile_features(cxx_std INTERFACE cxx_std_17)
aux_source_directory(./src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ./vulkan/include ./glfw/include ./include)
target_link_directories(${PROJECT_NAME} PUBLIC ./glfw/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC cxx_std glfw3 vulkan-1)

