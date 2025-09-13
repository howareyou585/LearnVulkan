#include <iostream>
#include "testVulkan.hpp"
// #define GLFW_INCLUDE_VULKAN
// #include "glfw/glfw3.h"
// using namespace std;
// const int width = 1280;
// const int height = 1080;
// const std::string title = "triangle";
int main()
{

    Test test;
    test.initWindow();
    test.initVulkan();
    test.run();
    //test.cleanupWindow();不需要调用，析构函数会处理
    // if(glfwInit()==GLFW_FALSE)
    // {
    //     std::cout<<"Failed to init glfw!" << std::endl;
    //     return -1;
    // }
    // glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    // glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    // GLFWwindow* window = glfwCreateWindow(width,height,title.c_str(),nullptr,nullptr);
    // if(!window)
    // {
    //     std::cout<<"Failed to create window!"<<std::endl;
    // }
    // while (!glfwWindowShouldClose(window))
    // {
    //     glfwPollEvents();
    // }
    
    // glfwDestroyWindow(window);
    // glfwTerminate();
    // std::cout << "hello world" << std::endl;
    return 0;
}