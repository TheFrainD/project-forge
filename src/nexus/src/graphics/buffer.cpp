#include "nexus/graphics/buffer.h"

#include <glad/glad.h>

#include "nexus/assert.h"
#include "nexus/sys/log.h"

namespace nx::graphics {

Buffer::~Buffer() { Release(); }

Buffer::Buffer(Buffer &&other) noexcept
    : id_(other.id_),
      usage_(other.usage_),
      target_(other.target_),
      size_(other.size_) {
    other.id_     = 0;
    other.size_   = 0;
    other.usage_  = Usage::kNone;
    other.target_ = Target::kNone;
}

Buffer &Buffer::operator=(Buffer &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(id_, other.id_);
        std::swap(size_, other.size_);
        std::swap(usage_, other.usage_);
        std::swap(target_, other.target_);
    }
    return *this;
}

outcome::Outcome<Buffer, outcome::Error> Buffer::Create(const Usage usage,
                                                        const Target target,
                                                        const size_t size,
                                                        const void *data) {
    uint32_t id = 0;
    glGenBuffers(1, &id);
    if (id == 0) {
        return outcome::Err<Buffer>(
            outcome::CreateError(ErrorCode::kFailedToGenerateBuffer));
    }

    NX_LOG_DEBUG("Created buffer with id: {}", id);

    Buffer buffer(id, usage, target, size);
    buffer.SetData(size, data);

    return outcome::Ok<Buffer, outcome::Error>(std::move(buffer));
}

void Buffer::SetData(const size_t size, const void *data) {
    NX_ASSERT(id_ != 0);

    Bind();
    glBufferData(static_cast<GLenum>(target_), static_cast<GLsizeiptr>(size),
                 data, static_cast<GLenum>(usage_));
    Unbind();
}

void Buffer::SetSubData(const size_t offset, const size_t size,
                        const void *data) {
    NX_ASSERT(id_ != 0);

    if (offset + size > size_) {
        NX_LOG_WARN("Buffer::SetSubData called with invalid offset and size.");
        return;
    }

    Bind();
    glBufferSubData(static_cast<GLenum>(target_), offset, size, data);
    Unbind();
}

void Buffer::Bind() const {
    NX_ASSERT(id_ != 0);
    glBindBuffer(static_cast<GLenum>(target_), id_);
}

void Buffer::BindRange(const uint32_t binding_point, const size_t size) {
    NX_ASSERT(id_ != 0);

    if (size > size_) {
        NX_LOG_WARN("Buffer::BindRange called with invalid size.");
        return;
    }

    glBindBufferRange(static_cast<GLenum>(target_), binding_point, id_, 0,
                      size);
}
void Buffer::BindBase(uint32_t binding_point) {
    NX_ASSERT(id_ != 0);
    glBindBufferBase(static_cast<GLenum>(target_), binding_point, id_);
}

void Buffer::Unbind() const {
    NX_ASSERT(id_ != 0);
    glBindBuffer(static_cast<GLenum>(target_), 0);
}

Buffer::Buffer(const uint32_t id, const Usage usage, const Target target,
               const size_t size)
    : id_(id), usage_(usage), target_(target), size_(size) {}

void Buffer::Release() {
    if (id_ != 0) {
        NX_LOG_DEBUG("Releasing buffer with id: {}", id_);

        glDeleteBuffers(1, &id_);
        id_     = 0;
        size_   = 0;
        usage_  = Usage::kNone;
        target_ = Target::kNone;
    }
}

}  // namespace nx::graphics