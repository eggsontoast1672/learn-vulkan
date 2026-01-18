#include "lvk/device.hpp"

#include <cstdint>
#include <stdexcept>
#include <vector>

#include <vulkan/vulkan.h>

#include "lvk/queue.hpp"

namespace lvk {

/// Check if the given physical device suits our needs.
///
/// Currently, the only thing we care about is if the GPU supports all of the
/// queue families we need.
static auto isDeviceSuitable(VkPhysicalDevice device) -> bool {
  const auto indices = findQueueFamilies(device);
  return indices.isComplete();
}

PhysicalDevice::PhysicalDevice(VkInstance instance) {
  uint32_t deviceCount{};
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    throw std::runtime_error("failed to find a GPU with vulkan support");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
  auto device = std::ranges::find_if(devices, isDeviceSuitable);
  if (device != devices.end()) {
    m_device = *device;
  } else {
    throw std::runtime_error("failed to find a suitable GPU");
  }
}

LogicalDevice::LogicalDevice(VkPhysicalDevice physicalDevice) {
  const auto indices = findQueueFamilies(physicalDevice);
  const auto queuePriority = 1.0f;

  VkDeviceQueueCreateInfo queueCreateInfo{};
  queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
  queueCreateInfo.queueCount = 1;
  queueCreateInfo.pQueuePriorities = &queuePriority;

  VkPhysicalDeviceFeatures deviceFeatures{};

  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.queueCreateInfoCount = 1;
  createInfo.pQueueCreateInfos = &queueCreateInfo;
  createInfo.pEnabledFeatures = &deviceFeatures;

  if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
    throw std::runtime_error("failed to create logical device");
  }
}

LogicalDevice::~LogicalDevice() {
  vkDestroyDevice(m_device, nullptr);
}

} // namespace lvk
