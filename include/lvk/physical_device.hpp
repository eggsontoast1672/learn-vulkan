#pragma once

typedef struct VkInstance_T *VkInstance;
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;

namespace lvk {

class PhysicalDevice {
public:
  /// Construct a physical device.
  ///
  /// The constructor searches the system for a graphics card that supports
  /// Vulkan and has all of the desired properties. Admittedly, this class is
  /// not very flexible in that regard, but that is okay, since it does not
  /// need to be.
  PhysicalDevice(VkInstance instance);

private:
  VkPhysicalDevice m_device;
};

} // namespace lvk
