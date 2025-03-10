#pragma once

#include <nexus/outcome/error.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>

#define NX_LOG_TRACE(...)    nx::sys::LoggerGet()->trace(__VA_ARGS__)
#define NX_LOG_DEBUG(...)    nx::sys::LoggerGet()->debug(__VA_ARGS__)
#define NX_LOG_INFO(...)     nx::sys::LoggerGet()->info(__VA_ARGS__)
#define NX_LOG_WARN(...)     nx::sys::LoggerGet()->warn(__VA_ARGS__)
#define NX_LOG_ERROR(...)    nx::sys::LoggerGet()->error(__VA_ARGS__)
#define NX_LOG_CRITICAL(...) nx::sys::LoggerGet()->critical(__VA_ARGS__)

namespace nx::sys {

/**
 * @brief Represents an error code for the logger subsystem.
 */
enum class LoggerErrorCode : std::uint8_t { kOk = 0, kAlreadyInitialized };

/**
 * @brief Initializes the logger subsystem.
 *
 * @param name The name of the logger.
 * @param path The path to the log file.
 * @return An error code.
 */
outcome::Error LoggerInit(const std::string &name, const std::string &path);

/**
 * @brief Gets the logger.
 *
 * @return The logger.
 */
std::shared_ptr<spdlog::logger> &LoggerGet();

}  // namespace nx::sys