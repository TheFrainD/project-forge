#include "nexus/graphics/shader_program.h"

#include <glad/glad.h>

#include "nexus/assert.h"
#include "nexus/sys/log.h"

namespace {

void AttachShader(const uint32_t id, const nx::graphics::Shader &shader) {
    NX_ASSERT(id != 0);
    NX_ASSERT(shader.GetId() == id);
    glAttachShader(id, shader.GetId());
}

void PrintInfoLog(const uint32_t id, const std::string &message) {
    NX_ASSERT(id != 0);

    GLint length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

    if (length == 0) {
        return;
    }

    std::vector<char> info_log(length);
    glGetProgramInfoLog(id, length, &length, info_log.data());

    NX_LOG_ERROR("{}{}", message.empty() ? "" : message + ": ",
                 std::string(info_log.begin(), info_log.end()));
}

}  // namespace

namespace nx::graphics {

ShaderProgram::~ShaderProgram() { Release(); }

ShaderProgram::ShaderProgram(ShaderProgram &&other) noexcept : id_(other.id_) {
    other.id_ = 0;
}

ShaderProgram &ShaderProgram::operator=(ShaderProgram &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(id_, other.id_);
    }
    return *this;
}
outcome::Outcome<ShaderProgram> ShaderProgram::Create(
    const std::optional<const Shader &> &vertex_shader,
    const std::optional<const Shader &> &fragment_shader,
    const std::optional<const Shader &> &geometry_shader) {
    const uint32_t id = glCreateProgram();
    if (id == 0) {
        return outcome::Err<ShaderProgram>(
            outcome::CreateError(ErrorCode::kFailedToCreateShaderProgram));
    }

    if (vertex_shader.has_value()) {
        AttachShader(id, *vertex_shader);
    }

    if (fragment_shader.has_value()) {
        AttachShader(id, *fragment_shader);
    }

    if (geometry_shader.has_value()) {
        AttachShader(id, *geometry_shader);
    }

    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        PrintInfoLog(id, "Failed to link shader program");
        glDeleteProgram(id);
        return outcome::Err<ShaderProgram>(
            outcome::CreateError(ErrorCode::kFailedToLinkShaderProgram));
    }

    NX_LOG_DEBUG("Created shader program with id: {}", id);

    return outcome::Ok(ShaderProgram(id));
}

void ShaderProgram::Use() const {
    NX_ASSERT(id_ != 0);
    glUseProgram(id_);
}

void ShaderProgram::Release() {
    if (id_ != 0) {
        glDeleteProgram(id_);
        NX_LOG_DEBUG("Deleted shader program with id: {}", id_);
        id_ = 0;
    }
}

ShaderProgram::ShaderProgram(uint32_t id) : id_(id) {}

}  // namespace nx::graphics