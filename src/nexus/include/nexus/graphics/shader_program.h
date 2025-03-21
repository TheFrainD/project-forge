#pragma once

#include <nexus/graphics/shader.h>
#include <nexus/outcome/outcome.h>

#include <cstdint>
#include <optional>

namespace nx::graphics {

class ShaderProgram {
public:
    enum class ErrorCode : uint8_t {
        kOk = 0,
        kFailedToCreateShaderProgram,
        kFailedToLinkShaderProgram
    };

    ~ShaderProgram();

    ShaderProgram(const ShaderProgram &)            = delete;
    ShaderProgram &operator=(const ShaderProgram &) = delete;

    ShaderProgram(ShaderProgram &&other) noexcept;
    ShaderProgram &operator=(ShaderProgram &&other) noexcept;

    /**
     * Create a new shader program.
     *
     * @param vertex_shader The vertex shader.
     * @param fragment_shader The fragment shader.
     * @param geometry_shader The geometry shader.
     * @return A new shader program.
     */
    [[nodiscard]] static outcome::Outcome<ShaderProgram> Create(
        const std::optional<const Shader &> &vertex_shader   = std::nullopt,
        const std::optional<const Shader &> &fragment_shader = std::nullopt,
        const std::optional<const Shader &> &geometry_shader = std::nullopt);

    /**
     * @brief Use the shader program.
     */
    void Use() const;

    /**
     * @brief Release the shader program.
     */
    void Release();

private:
    explicit ShaderProgram(uint32_t id);

    uint32_t id_;
}

}  // namespace nx::graphics