#pragma once

#include <nexus/outcome/error.h>

#include <cassert>
#include <variant>

namespace nx::outcome {

/**
 * @brief Represents an outcome.
 *
 * @tparam T The type of the value.
 * @tparam E The type of the error.
 */
template <typename T, typename E>
class Outcome {
public:
    explicit Outcome(const T &data) : data_(data) {}
    explicit Outcome(const E &error) : data_(error) {}

    explicit Outcome(E &&error) : data_(std::move(error)) {}
    explicit Outcome(T &&data) : data_(std::move(data)) {}

    /**
     * @brief Checks if the outcome is ok.
     *
     * @return True if the outcome is ok, false otherwise.
     */
    [[nodiscard]] bool IsOk() const { return std::holds_alternative<T>(data_); }

    /**
     * @brief Checks if the outcome is an error.
     *
     * @return True if the outcome is an error, false otherwise.
     */
    [[nodiscard]] bool IsError() const {
        return std::holds_alternative<E>(data_);
    }

    /**
     * @brief Gets the value.
     *
     * @return The value.
     */
    T &GetValue() {
        assert(IsOk());
        return std::get<T>(data_);
    }

    /**
     * @brief Gets the value.
     *
     * @return The value.
     */
    const T &GetValue() const {
        assert(IsOk());
        return std::get<T>(data_);
    }

    /**
     * @brief Gets the error.
     *
     * @return The error.
     */
    E &GetError() {
        assert(IsError());
        return std::get<E>(data_);
    }

    /**
     * @brief Gets the error.
     *
     * @return The error.
     */
    const E &GetError() const {
        assert(IsError());
        return std::get<E>(data_);
    }

private:
    std::variant<T, E> data_;
};

/**
 * @brief Creates an ok outcome.
 *
 * @tparam T The type of the value.
 * @tparam E The type of the error.
 * @param value The value.
 * @return The outcome.
 */
template <typename T, typename E>
Outcome<T, E> Ok(T value) {
    return Outcome<T, E>(std::move(value));
}

/**
 * @brief Creates an error outcome.
 *
 * @tparam T The type of the value.
 * @tparam E The type of the error.
 * @param error The error.
 * @return The outcome.
 */
template <typename T, typename E>
Outcome<T, E> Err(E error) {
    return Outcome<T, E>(std::move(error));
}

/**
 * @brief Represents an outcome with a default error type.
 *
 * @tparam T The type of the value.
 */
using DefaultOutcome = Outcome<void, Error>;

}  // namespace nx::outcome
