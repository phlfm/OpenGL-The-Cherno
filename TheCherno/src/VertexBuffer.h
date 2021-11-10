#pragma once
#ifndef H_VERTEXBUFFER
#define H_VERTEXBUFFER

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID = 0;
};

#endif // H_VERTEXBUFFER