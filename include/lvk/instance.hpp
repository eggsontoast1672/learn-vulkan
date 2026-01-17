#pragma once

#include <cstring>

#include <vulkan/vulkan_core.h>

namespace lvk {

/// The vulkan instance.
///
/// On a high level, the instance is like a handle to the Vulkan API, and thus
/// to the GPU. This type is responsible for setting up the instance, which
/// includes polling the host system for extensions and validation layers, and
/// setting up debug messages.
class Instance {
public:
  Instance();
  ~Instance();

  Instance(const Instance &) = delete;
  void operator=(const Instance &) = delete;

private:
  VkInstance m_instance;
  VkDebugUtilsMessengerEXT m_messenger;

  /// Configure the debug messenger.
  ///
  /// The debug messenger is what allows us to print debug info to the console
  /// while the app is running. This function configures the debug messenger
  /// to print all possible information messages, warnings, and errors.
  auto setupDebugMessenger() -> void;
};

} // namespace lvk
