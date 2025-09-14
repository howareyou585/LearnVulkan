#include "testVulkan.hpp"
#include <vector>
#include <cstring>
const std::vector<const char *> LayerNames = {
    "VK_LAYER_KHRONOS_validation"};
Test::Test() : Test({1280, 1080, "triangle"})
{
}
Test::Test(windowInfo wi) : m_wininfo(wi), m_window(nullptr)
{
    // 初始化window
    initWindow();
    // 初始化Vulkan
    initVulkan();
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

void Test::initVulkan()
{
    createInstance();
    setupMessenger();
}
void Test::createInstance()
{
    if (enableValidationLayer && !checkValidationLayerSupport())
    {
        throw runtime_error("validation layer is not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_4;
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    uint32_t glfwExtensionCount;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> Extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (enableValidationLayer)
    {
        Extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = Extensions.size();
    createInfo.ppEnabledExtensionNames = Extensions.data();
    if (enableValidationLayer)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(LayerNames.size());
        createInfo.ppEnabledLayerNames = LayerNames.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }
    // for(int index = 0; index < glfwExtensionCount; index++)
    // {
    //     std::cout<< *(glfwExtensions+index)<< std::endl;
    // }
    VkResult res = vkCreateInstance(&createInfo, nullptr, &m_vkInstance);
    if (res != VkResult::VK_SUCCESS)
    {
        switch (res)
        {
        case VkResult::VK_ERROR_INCOMPATIBLE_DRIVER:
            /* code */
            std::cout << "driver desn't support vulkan!" << std::endl;
            break;
        case VkResult::VK_ERROR_EXTENSION_NOT_PRESENT:
            std::cout << "vulkan couldn't support extensions you provided!" << std::endl;
            break;
        default:
            std::cout << "unknown error" << std::endl;
            break;
        }
        throw std::runtime_error("failed to create vkInstance");
    }
}
bool Test::checkValidationLayerSupport()
{
    vkEnumerateInstanceLayerProperties(&m_avaliableLayerCount, nullptr);
    std::vector<VkLayerProperties> availableLayerProperties(m_avaliableLayerCount);
    vkEnumerateInstanceLayerProperties(&m_avaliableLayerCount, availableLayerProperties.data());
    for (const char *layerName : LayerNames)
    {
        bool layerFound = false;
        for (const auto &layerProperty : availableLayerProperties)
        {
            if (strcmp(layerName, layerProperty.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }
        if (!layerFound)
        {
            return false;
        }
    }
    return true;
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
    if(enableValidationLayer)
    {
        destroyDebugUtilsMessenger(m_vkInstance,m_debugMessengerExt,nullptr);
    }
    vkDestroyInstance(m_vkInstance, nullptr); // 放在前面
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Test::cleanupAll()
{
    cleanupWindow();
}

VKAPI_ATTR VkBool32 VKAPI_CALL Test::debugCallBack(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *messengerData,
    void *pUserData)
{
    //     typedef VkBool32 (VKAPI_PTR *PFN_vkDebugUtilsMessengerCallbackEXT)(
    // VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
    // VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,
    // const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
    // void*                                            pUserData);
}

void Test::setupMessenger()
{
}
void Test::populateDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &debugUtilsMessenger)
{
    debugUtilsMessenger = {};
    debugUtilsMessenger.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugUtilsMessenger.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                                          VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                          VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
    debugUtilsMessenger.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                      VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
                                      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    debugUtilsMessenger.pfnUserCallback = debugCallBack;
    debugUtilsMessenger.pUserData = nullptr;
}

VkResult Test::createDebugUtilsMessenger(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT *createInfo,
                                     VkAllocationCallbacks *allocation, VkDebugUtilsMessengerEXT *debugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if(func==nullptr)
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    else
    {
        return func(instance, createInfo, allocation, debugMessenger);
    }   
}
void Test::destroyDebugUtilsMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, VkAllocationCallbacks *allocation)
{
    //PFN_vkDestroyDebugUtilsMessengerEXT
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
    if(func)
    {
        func(instance, debugMessenger, allocation);
    }   
}