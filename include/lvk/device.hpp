#pragma once

using VkDevice = struct VkDevice_T *;
using VkInstance = struct VkInstance_T *;
using VkPhysicalDevice = struct VkPhysicalDevice_T *;

namespace lvk {

class PhysicalDevice {
public:
  /// Construct the physical device.
  ///
  /// The constructor searches the system for a graphics card that supports
  /// Vulkan and has all of the desired properties. Admittedly, this class is
  /// not very flexible in that regard, but that is okay, since it does not
  /// need to be.
  explicit PhysicalDevice(VkInstance instance);

  /// Get the underlying handle.
  [[nodiscard]] inline auto getHandle() const -> VkPhysicalDevice { return m_device; }

private:
  VkPhysicalDevice m_device;
};

/// The logical device.
///
/// It is the responsibility of the logical device to keep track of what GPU
/// features and queues we will be using.
class LogicalDevice {
public:
  /// Construct the logical device.
  explicit LogicalDevice(VkPhysicalDevice physicalDevice);

  /// Destruct the logical device.
  ~LogicalDevice();

  LogicalDevice(const LogicalDevice &) = delete;
  LogicalDevice &operator=(const LogicalDevice &) = delete;

private:
  VkDevice m_device;
};

} // namespace lvk
