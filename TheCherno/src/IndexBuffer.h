#pragma once
#ifndef H_INDEXBUFFER
#define H_INDEXBUFFER

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int get_count() const { return m_Count; }

private:
	unsigned int m_rendererID = 0;
	unsigned int m_Count = 0;
};

#endif // H_INDEXBUFFER