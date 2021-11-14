#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void
VertexArray::add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.get_elements();
	unsigned int offset{ 0 };
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		// The line below (glVertexAttribPointer) "links" the array_buffer with the VAO
		GLCall(glVertexAttribPointer(
			i, element.count, element.type, element.normalized,
			layout.get_stride(), (const void*)offset)
		);
		offset += element.count * VertexBufferElement::get_type_size(element.type);
	}
}

void
VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}

void
VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_rendererID));
}
