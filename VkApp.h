//
// Created by kami on 1/1/22.
//

#ifndef LEARNINGVULKAN_VKAPP_H
#define LEARNINGVULKAN_VKAPP_H
#include <iostream>
#include <vector>
#include <set>
#include <cstdint> // Necessary for UINT32_MAX
#include <algorithm> // Necessary for std::clamp
#include <optional>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vulkan.h>
#include <GLFW/glfw3.h>



class VkApp {
public:
    void run(){
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
private:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    GLFWwindow* window;
    VkInstance vkInstance;
    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation",
//            "VK_LAYER_RENDERDOC_Capture"
    };
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
    bool checkValidationLayerSupport();


    bool checkGLFWSupportedExtensions();

    std::vector<const char*> getRequiredGlfwExtensions();

    void initWindow();
    void initVulkan();
    void createVkInstance();
    void mainLoop();
    void cleanup();


    //DEBUG
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
    VkDebugUtilsMessengerEXT debugMessenger;
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);
    void setupDebugMessenger();

    //Window surface
    VkSurfaceKHR surface;
    void createSurface();

    //Physical Device
    VkPhysicalDevice physicalDevice;
    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice);
    //physical device queues
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
    //physical device extensions
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);



    //logical Device
    VkDevice logicalDevice;
    void createLogicalDevice();

    //Queues
    VkQueue graphicsQueue;
    VkQueue presentQueue;


    //Swapchain
    VkSwapchainKHR swapChain;
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>&);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>&);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);
    void createSwapChain();


    //Images
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;
    void createImageViews();
    
    //Shaders
    VkShaderModule createShaderModule(const std::vector<char>& code);

    //Render pass
    VkRenderPass renderPass;

    //Pipeline Layout
    VkPipelineLayout pipelineLayout;

    //Render Pass
    void createRenderPass();

    //Graphics Pipeline
    void createGraphicsPipeline();
    VkPipeline graphicsPipeline;

    //Framebuffers
    std::vector<VkFramebuffer> swapChainFramebuffers;
    void createFramebuffers();

    //Command Pool
    VkCommandPool commandPool;
    void createCommandPool();

    //Command Buffers
    std::vector<VkCommandBuffer> commandBuffers;
    void createCommandBuffers();

    //Drawing the frame
    void drawFrame();

    //Semaphores
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    void createSemaphores();


};


#endif //LEARNINGVULKAN_VKAPP_H
