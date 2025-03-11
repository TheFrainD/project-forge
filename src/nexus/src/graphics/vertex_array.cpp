#include "nexus/graphics/vertex_array.h"

#include <glad/glad.h>

#include "nexus/assert.h"
#include "nexus/sys/log.h"

namespace nx::graphics {

VertexArray::~VertexArray() { Release(); }

VertexArray::VertexArray(VertexArray &&other) noexcept : id_(other.id_) {
    other.id_ = 0;
}
VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(id_, other.id_);
    }
    return *this;
}

outcome::Outcome<VertexArray> VertexArray::Create() {
    uint32_t id = 0;
    glGenVertexArrays(1, &id);
    if (id == 0) {
        return outcome::Err<VertexArray>(
            outcome::CreateError(ErrorCode::kFailedToGenerateVertexArray));
    }
    NX_LOG_DEBUG("Create vertex array with id: {}", id);
    return outcome::Ok<VertexArray>(VertexArray(id));
}

void VertexArray::Bind() const {
    NX_ASSERT(id_ != 0);
    glBindVertexArray(id_);
}

void VertexArray::Unbind() { glBindVertexArray(0); }

void VertexArray::ArrayAttrib(const uint32_t index, const int32_t size,
                              const DataType type, const int32_t stride,
                              const void *data) const {
    NX_ASSERT(id_ != 0);
    Bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, static_cast<GLenum>(type), GL_FALSE,
                          stride, data);
}

void VertexArray::Release() {
    if (id_ != 0) {
        glDeleteVertexArrays(1, &id_);
        NX_LOG_DEBUG("Deleted vertex array with id: {}", id_);
        id_ = 0;
    }
}

VertexArray::VertexArray(const uint32_t id) : id_(id) {}

}  // namespace nx::graphics