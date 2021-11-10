#pragma once
#ifndef H_VERTEXARRAY
#define H_VERTEXARRAY

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void add_buffer(const VertexBuffer &vb, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;
};

#endif // H_VERTEXARRAY