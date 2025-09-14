#ifndef TEST_VULKAN_INCLUDE
#define TEST_VULKAN_INCLUDE

#include <iostream>
#include <string>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include "glfw/glfw3.h"
using namespace std;
// VK_LAYER_KHRONOS_validation
#ifdef NDEBUG
const bool enableValidationLayer = false;
#else
const bool enableValidationLayer = true;
#endif
extern const std::vector<const char*>LayerNames; 
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
    void run();
    void cleanupWindow();

private:
    void initVulkan();
    void initWindow();
    void cleanupAll();
    bool checkValidationLayerSupport();

private:
    windowInfo m_wininfo;
    GLFWwindow *m_window;
    VkInstance m_vkInstance;
    uint32_t m_avaliableLayerCount;
};
#endif // !
