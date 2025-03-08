#pragma once

#include <cstdint>
#include <type_traits>

namespace nx::math {

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct Dimensions {
    T width;
    T height;

    bool operator==(const Dimensions& other) const {
        return width == other.width && height == other.height;
    }

    bool operator!=(const Dimensions& other) const {
        return !(*this == other);
    }
};

}  // namespace nx::math