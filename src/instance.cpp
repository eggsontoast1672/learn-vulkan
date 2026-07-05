#include "lvk/instance.hpp"

#include <cstring>
#include <format>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

namespace lvk {

static const std::array<const char *, 1> desiredLayers{
    "VK_LAYER_KHRONOS_validation",
};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

/// Retrieve a list of the required extensions.
///
/// This function returns a vector containing the names of the extensions that
/// the current Vulkan implementation needs to support. This includes all of
/// the extensions required by the windowing system, and optionally a debug
/// extension if validation layers are enabled.
static auto getRequiredExtensions() -> std::vector<const char *> {
  uint32_t glfwExtensionCount{};
  auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  std::vector requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  // If we are using validation layers, we would like hook into that
  // functionality and define our own debug message callback. In order to do
  // that, we need this extension.
  if (enableValidationLayers) {
    requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  return requiredExtensions;
}

/// Ensure that all desired validation layers are supported.
///
/// This function retrieves the list supported validation layers and ensures
/// that every layer that we want is available. If at least one is not
/// supported, this function returns false. Otherwise, true is returned.
static auto checkValidationLayerSupport() -> bool {
  uint32_t enabledLayerCount{};
  vkEnumerateInstanceLayerProperties(&enabledLayerCount, nullptr);
  std::vector<VkLayerProperties> enabledLayers(enabledLayerCount);
  vkEnumerateInstanceLayerProperties(&enabledLayerCount, enabledLayers.data());

  for (auto desiredLayer : desiredLayers) {
    auto layerFound = false;

    for (const auto &enabledLayer : enabledLayers) {
      if (std::strcmp(enabledLayer.layerName, desiredLayer) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}

/// The debug callback.
static VKAPI_ATTR auto VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *userData) -> VkBool32 {
  std::cerr << std::format("validation layer: {}\n", pCallbackData->pMessage);
  return VK_FALSE;
}

/// Construct the debug messenger.
///
/// Since the `vkCreateDebugUtilsMessengerEXT` function is provided by an
/// extension, it is not loaded by default. This function wraps the dynamic
/// loading of that function. If we were to just use
/// `vkCreateDebugUtilsMessengerEXT` directly, we would get a linker error
/// upon trying to build the application. Do not ask me how I know.
static auto createDebugUtilsMessenger(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger) -> VkResult {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

/// Destroy the debug messenger.
///
/// We need this wrapper function for the same reasons as above.
static auto destroyDebugUtilsMessenger(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks *pAllocator) -> void {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

/// Populate the debug messenger create info.
///
/// Since we need this information to create the instance and to set up the
/// debug messenger (and it is no big deal to initialize the create info twice)
/// we put it into this function to easily repeat it.
static auto populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.pNext = nullptr;
  createInfo.flags = 0;
  createInfo.messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType =
      VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debugCallback;
  createInfo.pUserData = nullptr;
}

Instance::Instance() {
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Learn Vulkan";
  appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  auto extensions = getRequiredExtensions();

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = extensions.size();
  createInfo.ppEnabledExtensionNames = extensions.data();
  if (enableValidationLayers) {
    auto layersSupported = checkValidationLayerSupport();
    if (!layersSupported) {
      throw std::runtime_error("one or more desired validation layers not supported");
    }

    createInfo.enabledLayerCount = desiredLayers.size();
    createInfo.ppEnabledLayerNames = desiredLayers.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    populateDebugMessengerCreateInfo(debugCreateInfo);
    createInfo.pNext = &debugCreateInfo;
  }

  if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
    throw std::runtime_error("failed to create instance");
  }
}

Instance::~Instance() {
  if (enableValidationLayers) {
    destroyDebugUtilsMessenger(m_instance, m_messenger, nullptr);
  }

  vkDestroyInstance(m_instance, nullptr);
}

auto Instance::setupDebugMessenger() -> void {
  if (!enableValidationLayers) {
    return;
  }

  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  populateDebugMessengerCreateInfo(createInfo);
  if (createDebugUtilsMessenger(m_instance, &createInfo, nullptr, &m_messenger)) {
    throw std::runtime_error("failed to set up debug messenger");
  }
}

} // namespace lvk
