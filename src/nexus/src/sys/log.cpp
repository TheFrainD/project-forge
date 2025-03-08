#include "nexus/sys/log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <vector>

namespace nx::sys {

struct LoggerSubsystem {
    std::shared_ptr<spdlog::logger> logger;

    bool initialized {false};
};

static LoggerSubsystem g_logger_subsystem;

outcome::Error LoggerInit(const std::string &name, const std::string &path) {
    if (g_logger_subsystem.initialized) {
        return outcome::CreateError(LoggerErrorCode::kAlreadyInitialized);
    }

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.push_back(
        std::make_shared<spdlog::sinks::basic_file_sink_mt>(path, true));

    g_logger_subsystem.logger =
        std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
    spdlog::register_logger(g_logger_subsystem.logger);
    g_logger_subsystem.logger->set_level(spdlog::level::trace);
    g_logger_subsystem.logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    g_logger_subsystem.initialized = true;

    return outcome::CreateError(LoggerErrorCode::kOk);
}

std::shared_ptr<spdlog::logger> &LoggerGet() {
    return g_logger_subsystem.logger;
}

}  // namespace nx::sys