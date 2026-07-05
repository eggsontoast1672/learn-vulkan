#include "lvk/queue.hpp"

#include <optional>
#include <vector>

#include <vulkan/vulkan.h>

namespace lvk {

auto QueueFamilyIndices::isComplete() const -> bool {
  return this->graphicsFamily.has_value();
}

auto findQueueFamilies(VkPhysicalDevice device) -> QueueFamilyIndices {
  uint32_t queueFamilyCount{};
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  QueueFamilyIndices indices{};
  int queueFamilyIndex = 0;
  for (const auto &queueFamily : queueFamilies) {
    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = queueFamilyIndex;
    }

    if (indices.isComplete()) {
      break;
    }

    queueFamilyIndex++;
  }

  return indices;
}

} // namespace lvk
