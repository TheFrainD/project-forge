#include "nexus/graphics/shader.h"

#include <glad/glad.h>

#include "nexus/assert.h"
#include "nexus/sys/log.h"

namespace {

void PrintInfoLog(const uint32_t id, const std::string &message) {
    NX_ASSERT(id != 0);

    GLint length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    if (length == 0) {
        return;
    }

    std::vector<char> info_log(length);
    glGetShaderInfoLog(id, length, &length, info_log.data());

    NX_LOG_ERROR("{}{}", message.empty() ? "" : message + ": ",
                 std::string(info_log.begin(), info_log.end()));
}

}  // namespace

namespace nx::graphics {

Shader::~Shader() { Release(); }

Shader::Shader(Shader &&other) noexcept : id_(other.id_) { other.id_ = 0; }

Shader &Shader::operator=(Shader &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(id_, other.id_);
    }
    return *this;
}

outcome::Outcome<Shader> Shader::Create(Type type, const std::string &source) {
    uint32_t id = glCreateShader(static_cast<GLenum>(type));
    if (id == 0) {
        return outcome::Err<Shader>(
            outcome::CreateError(ErrorCode::kFailedToCreateShader));
    }

    glShaderSource(
        id, 1, reinterpret_cast<const GLchar *const *>(source.data()), nullptr);
    glCompileShader(id);

    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        PrintInfoLog(id, "Failed to compile shader");
        glDeleteShader(id);
        return outcome::Err<Shader>(
            outcome::CreateError(ErrorCode::kFailedToCompileShader));
    }

    NX_LOG_DEBUG("Created shader with id: {}", id);

    return outcome::Ok(Shader(id));
}
uint32_t Shader::GetId() const {
    NX_ASSERT(id_ != 0);
    return id_;
}

void Shader::Release() {
    if (id_ != 0) {
        glDeleteShader(id_);
        NX_LOG_DEBUG("Deleted shader with id: {}", id_);
        id_ = 0;
    }
}

Shader::Shader(const uint32_t id) : id_(id) {}

}  // namespace nx::graphics