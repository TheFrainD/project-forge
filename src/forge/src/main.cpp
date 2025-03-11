#include <nexus/graphics/buffer.h>
#include <nexus/sys/log.h>
#include <nexus/sys/window.h>

#include <iostream>
#include <memory>
#include <vector>

int main(int, char *[]) {
    if (const auto error = nx::sys::LoggerInit("forge", "forge.log");
        !error.IsOk()) {
        switch (error.GetCode<nx::sys::LoggerErrorCode>()) {
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

    nx::sys::WindowSettings settings;
    settings.dimensions = nx::math::Dimensions<int>(800, 600);
    settings.title      = "forge";

    if (const auto error = nx::sys::WindowInit(settings); !error.IsOk()) {
        switch (error.GetCode<nx::sys::WindowErrorCode>()) {
            case nx::sys::WindowErrorCode::kAlreadyInitialized:
                NX_LOG_ERROR("Window subsystem already initialized");
                break;
            case nx::sys::WindowErrorCode::kFailedToInitializeGLFW:
                NX_LOG_ERROR("Failed to initialize GLFW");
                break;
            case nx::sys::WindowErrorCode::kFailedToCreateGLFWWindow:
                NX_LOG_ERROR("Failed to create GLFW window");
                break;
            case nx::sys::WindowErrorCode::kFailedToInitializeGLAD:
                NX_LOG_ERROR("Failed to initialize GLAD");
                break;
            default:
                NX_LOG_ERROR("Unknown error");
                break;
        }
        return 1;
    }

    auto buffer_outcome = nx::graphics::Buffer::Create(
        nx::graphics::Buffer::Usage::kStaticDraw,
        nx::graphics::Buffer::Target::kArrayBuffer, 0);
    std::unique_ptr<nx::graphics::Buffer> buffer;
    if (buffer_outcome.IsOk()) {
        const std::vector test_data = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

        buffer = std::make_unique<nx::graphics::Buffer>(
            std::move(buffer_outcome.GetValue()));
        buffer->SetData(test_data.size() * sizeof(float), test_data.data());
    }

    while (!nx::sys::WindowShouldClose()) {
        nx::sys::WindowPollEvents();
        nx::sys::WindowSwapBuffers();

        buffer->Bind();
    }

    buffer->Release();
    nx::sys::WindowDeinit();
    return 0;
}
