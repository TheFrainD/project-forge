#pragma once

#include <cstdint>
#include <string>

#include "nexus/math/dimensions.h"
#include "nexus/outcome/error.h"

struct GLFWwindow;

namespace nx::sys {

struct WindowSettings {
    math::Dimensions<int> dimensions;
    std::string title;
};

enum class WindowErrorCode : std::uint8_t {
    kOk = 0,
    kAlreadyInitialized,
    kFailedToInitializeGLFW,
    kFailedToCreateGLFWWindow,
    kFailedToInitializeGLAD
};

outcome::Error WindowInit(const WindowSettings &settings);

void WindowDeinit();

bool WindowShouldClose();

void WindowPollEvents();

void WindowSwapBuffers();

math::Dimensions<int> WindowGetDimensions();

std::string WindowGetTitle();

}  // namespace nx::sys