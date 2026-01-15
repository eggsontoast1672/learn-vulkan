# Learn Vulkan

My adventures learning the Vulkan API. I am following along with the official
Khronos documentation for the API.

## Notes

According to the docs, this is what it takes to draw a triangle. This is all
paraphrased from the tutorial, but I feel compelled to write it down here so I
can understand it better.

1. Instance and physical device selection
2. Logical device and queue families
3. Window surface and swap chain
4. Image views and dynamic rendering
5. Dynamic rendering overview
6. Graphics pipeline
7. Command pools and command buffers
8. Main loop

To initialize Vulkan, you have to create a `vk::Instance` object. The Vulkan
instance is like an OpenGL context. Once you have the context, you can begin to
make API calls. Once you have the instance, you can use it to query the host
system for one of more `vk::PhysicalDevice` objects. Based on some criteria,
you can decide which one you want to use for rendering. In this project it does
not really matter, so as long as there is at least one available, I will just
select the first available device.

The next step is to create a logical device using the `vk::Device` class which
contains in-memory configuration about features that the program will use.
Then, we need a `vk::Queue` which will facilitate asynchronous operations.

Of course, we would like to present the things we are rendering to some sort of
window. Just like OpenGL, the Vulkan API itself does not provide tools for
creating windows. For that, we will need another library such as SDL or GLFW.
This project will use GLFW. To render to that window, we need two things: a
window surface, provided by `vk::SurfaceKHR`, and a swap chain, provided by
`vk::SwapchainKHR`. The former is sort of the Vulkan equivalent of an OpenGL
context being attached to a particular window. The latter ensures that we never
render to the same surface that is currently being displayed in the window. The
"KHR" suffix on each of these types is due to the fact that they are heavily
tied to the windowing system and thus the operating system, but the core of the
Vulkan API is meant to be platform-agnostic.
