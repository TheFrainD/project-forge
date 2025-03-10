#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace nx::outcome {

/**
 * @brief Represents an error.
 */
class Error {
public:
    Error(std::string message, const std::uint8_t code)
        : message_(std::move(message)), code_(code) {}
    explicit Error(const std::uint8_t code) : code_(code) {}

    /**
     * @brief Gets the error message.
     *
     * @return The error message.
     */
    [[nodiscard]] const std::string &GetMessage() const { return message_; }

    /**
     * @brief Checks if the error has a message.
     *
     * @return True if the error has a message, false otherwise.
     */
    [[nodiscard]] bool HasMessage() const { return !message_.empty(); }

    /**
     * @brief Gets the error code.
     *
     * @tparam T The type of the error code.
     * @return The error code.
     */
    [[nodiscard]] std::uint8_t GetCode() const { return code_; }
    template <typename T>
    T GetCode() const {
        return static_cast<T>(code_);
    }

    /**
     * @brief Checks if the error is ok.
     *
     * @return True if the error is ok, false otherwise.
     */
    [[nodiscard]] bool IsOk() const { return code_ == 0; }

private:
    std::string message_;
    std::uint8_t code_;
};

/**
 * @brief Creates an error with a message and a code.
 *
 * @tparam T The type of the error code.
 * @param message The error message.
 * @param code The error code.
 * @return The error.
 */
template <typename T>
Error CreateError(const std::string &message, T code) {
    return {message, static_cast<std::uint8_t>(code)};
}

/**
 * @brief Creates an error with a code.
 *
 * @tparam T The type of the error code.
 * @param code The error code.
 * @return The error.
 */
template <typename T>
Error CreateError(T code) {
    return Error(static_cast<std::uint8_t>(code));
}

}  // namespace nx::outcome
