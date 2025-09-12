#include "testVulkan.hpp"
Test::Test() : Test({1280, 1080, "triangle"})
{
}
Test::Test(windowInfo wi) : m_wininfo(wi), m_window(nullptr)
{
}
Test::~Test()
{
    cleanupAll();
}
void Test::initWindow()
{
    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "Failed to init glfw!" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(m_wininfo.width, m_wininfo.height, m_wininfo.title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        std::cout << "Failed to create window!" << std::endl;
    }
}
void Test::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
    }
}
void Test::cleanupWindow()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Test::cleanupAll()
{
    cleanupWindow();
}