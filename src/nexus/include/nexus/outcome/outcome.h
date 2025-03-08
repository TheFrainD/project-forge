#pragma once

#include <variant>
#include <cassert>

#include "nexus/outcome/error.h"

namespace nx::outcome {

template <typename T, typename E>
class Outcome {
public:
    Outcome(const T &data) : data_(data) {}
    Outcome(const E &error) : data_(error) {}

    Outcome(E &&error) : data_(std::move(error)) {}
    Outcome(T &&data) : data_(std::move(data)) {}

    bool IsOk() const { return std::holds_alternative<T>(data_); }

    bool IsError() const { return std::holds_alternative<E>(data_); }

    T &GetValue() {
        assert(IsOk());
        return std::get<T>(data_);
    }

    const T& GetValue() const {
        assert(IsOk());
        return std::get<T>(data_);
    }

    E &GetError() {
        assert(IsError());
        return std::get<E>(data_);
    }

    const E& GetError() const {
        assert(IsError());
        return std::get<E>(data_);
    }
private:
    std::variant<T, E> data_;
};

template <typename T, typename E>
Outcome<T, E> Ok(T value) {
    return Outcome<T, E>(std::move(value));
}

template <typename T, typename E>
Outcome<T, E> Err(E error) {
    return Outcome<T, E>(std::move(error));
}

using DefaultOutcome = Outcome<void, Error>;

}  // namespace nx::outcome