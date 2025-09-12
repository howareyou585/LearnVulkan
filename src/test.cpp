#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include "glfw/glfw3.h"
using namespace std;
const int width = 1280;
const int height = 1080;
const std::string title = "triangle";
int main()
{

    if(glfwInit()==GLFW_FALSE)
    {
        std::cout<<"Failed to init glfw!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(width,height,title.c_str(),nullptr,nullptr);
    if(!window)
    {
        std::cout<<"Failed to create window!"<<std::endl;
    }
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "hello world" << std::endl;
    return 0;
}