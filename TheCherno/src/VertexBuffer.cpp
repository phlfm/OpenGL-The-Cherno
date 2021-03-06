#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    // generate 1 buffer and assign it an id
    GLCall(glGenBuffers(1, &m_rendererID));
    // select the buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    // specify size in bytes. Could be sizeof(positions) and pass it data
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void
VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void
VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
