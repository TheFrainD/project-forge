#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

#include "nexus/outcome/error.h"

#define LOG_TRACE(...)    nx::sys::LoggerGet()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    nx::sys::LoggerGet()->debug(__VA_ARGS__)
#define LOG_INFO(...)     nx::sys::LoggerGet()->info(__VA_ARGS__)
#define LOG_WARN(...)     nx::sys::LoggerGet()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    nx::sys::LoggerGet()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) nx::sys::LoggerGet()->critical(__VA_ARGS__)

namespace nx::sys {

enum class LoggerErrorCode : std::uint8_t { kOk = 0, kAlreadyInitialized };

outcome::Error LoggerInit(const std::string &name, const std::string &path);

std::shared_ptr<spdlog::logger> &LoggerGet();

}  // namespace nx::sys