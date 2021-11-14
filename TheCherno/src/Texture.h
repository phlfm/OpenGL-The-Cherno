#pragma once
#ifndef H_TEXTURE
#define H_TEXTURE

#include "Renderer.h"
#include <string>

class Texture
{
private:
	unsigned int m_rendererID{ 0 };
	std::string m_filePath{""};
	unsigned char *m_localBuffer{ nullptr };
	int m_width{ 0 }, m_height{ 0 }, m_bpp{ 0 };

public:
	Texture(const std::string &path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
};

#endif // H_TEXTURE