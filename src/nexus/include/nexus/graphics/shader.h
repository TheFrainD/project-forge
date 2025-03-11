#pragma once

#include <nexus/outcome/outcome.h>

#include <cstdint>
#include <string>

namespace nx::graphics {

class Shader {
public:
    enum class ErrorCode : uint8_t {
        kOk = 0,
        kFailedToCreateShader,
        kFailedToCompileShader,
    };

    enum class Type : uint32_t {
        kVertex   = 0x8B31,
        kFragment = 0x8B30,
        kGeometry = 0x8DD9,
    };

    ~Shader();

    Shader(const Shader &)            = delete;
    Shader &operator=(const Shader &) = delete;

    Shader(Shader &&other) noexcept;
    Shader &operator=(Shader &&other) noexcept;

    /**
     * @brief Creates a shader.
     *
     * @param type The type of the shader.
     * @param source The source code of the shader.
     * @return An outcome with either shader or error.
     */
    static outcome::Outcome<Shader> Create(Type type,
                                           const std::string &source);

    uint32_t GetId() const;

    void Release();

private:
    explicit Shader(uint32_t id);

    uint32_t id_;
};

}  // namespace nx::graphics