#include <iostream>

#include "nexus/sys/log.h"
#include "nexus/sys/window.h"

int main(int, char *[]) {
    {
        auto error = nx::sys::LoggerInit("forge", "forge.log");
        if (!error.IsOk()) {
            auto code = error.GetCode<nx::sys::LoggerErrorCode>();
            switch (code) {
                case nx::sys::LoggerErrorCode::kAlreadyInitialized:
                    std::cerr << "Logger subsystem already initialized"
                              << std::endl;
                    break;
                default:
                    std::cerr << "Unknown error" << std::endl;
                    break;
            }
            return 1;
        }
    }

    nx::sys::WindowSettings settings;
    settings.dimensions = nx::math::Dimensions<int>(800, 600);
    settings.title      = "forge";

    {
        auto error = nx::sys::WindowInit(settings);
        if (!error.IsOk()) {
            auto code = error.GetCode<nx::sys::WindowErrorCode>();
            switch (code) {
                case nx::sys::WindowErrorCode::kAlreadyInitialized:
                    LOG_ERROR("Window subsystem already initialized");
                    break;
                case nx::sys::WindowErrorCode::kFailedToInitializeGLFW:
                    LOG_ERROR("Failed to initialize GLFW");
                    break;
                case nx::sys::WindowErrorCode::kFailedToCreateGLFWWindow:
                    LOG_ERROR("Failed to create GLFW window");
                    break;
                case nx::sys::WindowErrorCode::kFailedToInitializeGLAD:
                    LOG_ERROR("Failed to initialize GLAD");
                    break;
                default:
                    LOG_ERROR("Unknown error");
                    break;
            }
            return 1;
        }
    }

    while (!nx::sys::WindowShouldClose()) {
        nx::sys::WindowPollEvents();
        nx::sys::WindowSwapBuffers();
    }

    nx::sys::WindowDeinit();
    return 0;
}
