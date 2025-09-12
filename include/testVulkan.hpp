#ifndef TEST_VULKAN_INCLUDE
#define TEST_VULKAN_INCLUDE

#include <iostream>
#include <string>
 #define GLFW_INCLUDE_VULKAN
 #include "glfw/glfw3.h"
using namespace std;
struct windowInfo
{
     int width;
     int height;
     std::string title;
};
class Test
{
public:
    Test();
    Test(windowInfo wi);
    ~Test();

public:
    void initWindow();
    void run();
    void cleanupWindow();
private:
    
    void cleanupAll();

private:
     windowInfo m_wininfo;
     GLFWwindow *m_window;
};
#endif // !
