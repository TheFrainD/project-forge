#pragma once

#include <nexus/outcome/outcome.h>

#include <cstddef>
#include <cstdint>

namespace nx::graphics {

class Buffer {
public:
    enum class ErrorCode : uint8_t { kOk = 0, kFailedToGenerateBuffer };

    enum class Usage : uint32_t {
        kNone        = 0,
        kStreamDraw  = 0x88E0,
        kStreamRead  = 0x88E1,
        kStreamCopy  = 0x88E2,
        kStaticDraw  = 0x88E4,
        kStaticRead  = 0x88E5,
        kStaticCopy  = 0x88E6,
        kDynamicDraw = 0x88E8,
        kDynamicRead = 0x88E9,
        kDynamicCopy = 0x88EA
    };

    enum class Target : uint32_t {
        kNone               = 0,
        kArrayBuffer        = 0x8892,
        kElementArrayBuffer = 0x8893,
        kUniformBuffer      = 0x8A11
    };

    ~Buffer();

    Buffer(const Buffer &)            = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&other) noexcept;
    Buffer &operator=(Buffer &&other) noexcept;

    /**
     * @brief Creates a buffer.
     *
     * @param usage The usage of the buffer.
     * @param target The target of the buffer.
     * @param size The size of the buffer in bytes.
     * @param data A pointer to the data to be set. If nullptr, the buffer is
     * allocated but not initialized.
     */
    static outcome::Outcome<Buffer, outcome::Error> Create(
        Usage usage, Target target, size_t size, const void *data = nullptr);

    /**
     * @brief Sets the data for the buffer.
     *
     * This function binds the buffer, sets its data, and then unbinds it.
     *
     * @param size The size of the data in bytes.
     * @param data A pointer to the data to be set. If nullptr, the buffer is
     * allocated but not initialized.
     */
    void SetData(size_t size, const void *data);

    /**
     * @brief Sets a portion of the buffer's data.
     *
     * This function binds the buffer, sets the data, and then unbinds it.
     *
     * @param offset The offset in bytes from the beginning of the buffer.
     * @param size The size of the data in bytes.
     * @param data A pointer to the data to be set.
     */
    void SetSubData(size_t offset, size_t size, const void *data);

    /**
     * @brief Binds the buffer.
     */
    void Bind() const;

    /**
     * @brief Binds a range of the buffer.
     *
     * @param binding_point The binding point.
     * @param size The size of the range in bytes.
     */
    void BindRange(uint32_t binding_point, size_t size);

    /**
     * @brief Binds the buffer to a base.
     *
     * @param binding_point The binding point.
     */
    void BindBase(uint32_t binding_point);

    /**
     * @brief Unbinds the buffer.
     */
    void Unbind() const;

    /**
     * @brief Releases the buffer.
     */
    void Release();

private:
    Buffer(uint32_t id, Usage usage, Target target, size_t size);

    uint32_t id_;
    Usage usage_;
    Target target_;
    size_t size_;
};

}  // namespace nx::graphics
