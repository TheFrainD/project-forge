#pragma once

#include <cstdint>
#include <string>

namespace nx::outcome {

class Error {
public:
    Error(const std::string& message, std::uint8_t code)
        : message_(message), code_(code) {}
    Error(std::uint8_t code) : code_(code) {}

    const std::string& GetMessage() const { return message_; }
    bool HasMessage() const { return !message_.empty(); }

    template <typename T>
    T GetCode() const {
        return static_cast<T>(code_);
    }

    bool IsOk() const { return code_ == 0; }

private:
    std::string message_;
    std::uint8_t code_;
};

template <typename T>
Error CreateError(const std::string& message, T code) {
    return Error(message, static_cast<std::uint8_t>(code));
}

template <typename T>
Error CreateError(T code) {
    return Error(static_cast<std::uint8_t>(code));
}

}  // namespace nx::outcome