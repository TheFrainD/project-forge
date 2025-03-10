#pragma once

#include <nexus/math/dimensions.h>
#include <nexus/outcome/error.h>

#include <cstdint>
#include <string>

// Forward declaration of GLFWwindow.
struct GLFWwindow;

namespace nx::sys {

/**
 * @brief Represents the settings for a window.
 */
struct WindowSettings {
    math::Dimensions<int> dimensions;
    std::string title;
};

/**
 * @brief Represents an error code for the window subsystem.
 */
enum class WindowErrorCode : std::uint8_t {
    kOk = 0,
    kAlreadyInitialized,
    kFailedToInitializeGLFW,
    kFailedToCreateGLFWWindow,
    kFailedToInitializeGLAD
};

/**
 * @brief Initializes the window subsystem.
 *
 * @param settings The settings for the window.
 * @return An error code.
 */
outcome::Error WindowInit(const WindowSettings &settings);

/**
 * @brief Deinitializes the window subsystem.
 */
void WindowDeinit();

/**
 * @brief Checks if the window should close.
 *
 * @return True if the window should close, false otherwise.
 */
bool WindowShouldClose();

/**
 * @brief Polls events for the window.
 */
void WindowPollEvents();

/**
 * @brief Swaps the buffers for the window.
 */
void WindowSwapBuffers();

/**
 * @brief Gets the dimensions of the window.
 *
 * @return The dimensions of the window.
 */
math::Dimensions<int> WindowGetDimensions();

/**
 * @brief Gets the title of the window.
 *
 * @return The title of the window.
 */
std::string WindowGetTitle();

}  // namespace nx::sys