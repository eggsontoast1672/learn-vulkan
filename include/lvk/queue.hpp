#pragma once

#include <cstdint>
#include <optional>

using VkPhysicalDevice = struct VkPhysicalDevice_T *;

namespace lvk {

/// Contains indices of queue families that support desired operations.
///
/// For example, the `graphicsFamily` method will contain the index of a queue
/// family which supports graphics operations, if one exists. If one does not
/// exist, then it will hold a null optional.
struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;

  /// Check if the queue family supports all desired operations.
  ///
  /// If there is at least one operation that is not supported, e.g. some
  /// member of the struct is a null optional, this function returns false.
  /// Otherwise, true is returned.
  [[nodiscard]] auto isComplete() const -> bool;
};

/// Find the number of queue families which support various operations.
auto findQueueFamilies(VkPhysicalDevice device) -> QueueFamilyIndices;

}
