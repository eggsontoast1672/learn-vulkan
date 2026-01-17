#include "lvk/physical_device.hpp"

#include <cstdint>
#include <stdexcept>
#include <vector>

#include <vulkan/vulkan.h>

namespace lvk {

/// Check if the given physical device suits our needs.
///
/// There are many factors that we could check in here, such as VRAM size,
/// support for particular shaders, the maximum size of texture buffers,
/// whether or not the device is a discrete GPU, and many more. However, for
/// now we only care about Vulkan support, so we just return true.
static auto isDeviceSuitable(VkPhysicalDevice device) -> bool {
  return true;
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

} // namespace lvk
