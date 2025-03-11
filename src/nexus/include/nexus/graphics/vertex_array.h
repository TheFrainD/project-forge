#pragma once

#include <nexus/outcome/outcome.h>

#include <cstdint>

namespace nx::graphics {

class VertexArray {
public:
    enum class ErrorCode : uint8_t { kOk = 0, kFailedToGenerateVertexArray };

    enum class DataType {
        kByte          = 0x1400,
        kUnsignedByte  = 0x1401,
        kShort         = 0x1402,
        kUnsignedShort = 0x1403,
        kInt           = 0x1404,
        kUnsignedInt   = 0x1405,
        kFloat         = 0x1406,
        kDouble        = 0x140A
    };

    ~VertexArray();

    VertexArray(const VertexArray &)            = delete;
    VertexArray &operator=(const VertexArray &) = delete;

    VertexArray(VertexArray &&other) noexcept;
    VertexArray &operator=(VertexArray &&other) noexcept;

    /**
     * @brief Creates a vertex array.
     *
     * @return An outcome with either vertex array or error.
     */
    static outcome::Outcome<VertexArray> Create();

    /**
     * @brief Binds the vertex array.
     */
    void Bind() const;

    /**
     * @brief Unbinds the vertex array.
     */
    static void Unbind();

    /**
     * @brief Defines an array of generic vertex attribute data
     *
     * @param index Specifies the index of the generic vertex attribute to be
     * modified.
     * @param size Specifies the number of components per generic vertex
     * attribute.
     * @param type Specifies the data type of each component in the array.
     * @param stride Specifies the byte offset between consecutive generic
     * vertex attributes.
     * @param data Specifies a offset of the first component of the first
     * generic vertex attribute in the array in the data store of the buffer
     * currently bound to the GL_ARRAY_BUFFER target.
     */
    void ArrayAttrib(uint32_t index, int32_t size, DataType type,
                     int32_t stride, const void *data) const;

    /**
     * @brief Releases the vertex array.
     */
    void Release();

private:
    explicit VertexArray(uint32_t id);

    uint32_t id_;
};

}  // namespace nx::graphics