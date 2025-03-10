#include "nexus/sys/window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "nexus/assert.h"
#include "nexus/sys/log.h"

namespace nx::sys {

struct WindowSubsystem {
    GLFWwindow *window {nullptr};
    math::Dimensions<int> dimensions {};
    std::string title;

    bool initialized {false};
};

static WindowSubsystem g_window_subsystem;

outcome::Error WindowInit(const WindowSettings &settings) {
    NX_ASSERT_MSG(g_window_subsystem.initialized == false,
                  "Window subsystem already initialized");

    if (g_window_subsystem.initialized) {
        return outcome::CreateError(WindowErrorCode::kAlreadyInitialized);
    }

    glfwSetErrorCallback([](int error, const char *description) {
        NX_LOG_ERROR("GLFW error: {} - {}", error, description);
    });

    if (!glfwInit()) {
        return outcome::CreateError(WindowErrorCode::kFailedToInitializeGLFW);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif

    g_window_subsystem.dimensions = settings.dimensions;
    g_window_subsystem.title      = settings.title;

    g_window_subsystem.window =
        glfwCreateWindow(g_window_subsystem.dimensions.width,
                         g_window_subsystem.dimensions.height,
                         g_window_subsystem.title.c_str(), nullptr, nullptr);
    if (!g_window_subsystem.window) {
        glfwTerminate();
        return outcome::CreateError(WindowErrorCode::kFailedToCreateGLFWWindow);
    }

    glfwSetFramebufferSizeCallback(
        g_window_subsystem.window,
        [](GLFWwindow *, const int width, const int height) {
            glViewport(0, 0, width, height);
        });

    glfwSetWindowSizeCallback(g_window_subsystem.window, [](GLFWwindow *window,
                                                            const int width,
                                                            const int height) {
        auto *subsystem =
            static_cast<WindowSubsystem *>(glfwGetWindowUserPointer(window));
        subsystem->dimensions.width  = width;
        subsystem->dimensions.height = height;
    });

    glfwSetWindowUserPointer(g_window_subsystem.window, &g_window_subsystem);
    glfwMakeContextCurrent(g_window_subsystem.window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(g_window_subsystem.window);
        g_window_subsystem.window = nullptr;
        glfwTerminate();
        return outcome::CreateError(WindowErrorCode::kFailedToInitializeGLAD);
    }

    math::Dimensions<int> framebuffer_dimensions;
    glfwGetFramebufferSize(g_window_subsystem.window,
                           &framebuffer_dimensions.width,
                           &framebuffer_dimensions.height);
    glViewport(0, 0, framebuffer_dimensions.width,
               framebuffer_dimensions.height);

    g_window_subsystem.initialized = true;
    return outcome::CreateError(WindowErrorCode::kOk);
}

void WindowDeinit() {
    if (g_window_subsystem.window) {
        glfwDestroyWindow(g_window_subsystem.window);
        g_window_subsystem.window = nullptr;
    }

    if (g_window_subsystem.initialized) {
        glfwTerminate();
    }
}

bool WindowShouldClose() {
    NX_ASSERT_MSG(g_window_subsystem.initialized,
                  "Window subsystem not initialized");
    return glfwWindowShouldClose(g_window_subsystem.window);
}

void WindowPollEvents() {
    NX_ASSERT_MSG(g_window_subsystem.initialized,
                  "Window subsystem not initialized");
    glfwPollEvents();
};

void WindowSwapBuffers() {
    NX_ASSERT_MSG(g_window_subsystem.initialized,
                  "Window subsystem not initialized");
    glfwSwapBuffers(g_window_subsystem.window);
}

math::Dimensions<int> WindowGetDimensions() {
    NX_ASSERT_MSG(g_window_subsystem.initialized,
                  "Window subsystem not initialized");
    return g_window_subsystem.dimensions;
}

std::string WindowGetTitle() {
    NX_ASSERT_MSG(g_window_subsystem.initialized,
                  "Window subsystem not initialized");
    return g_window_subsystem.title;
}

}  // namespace nx::sys