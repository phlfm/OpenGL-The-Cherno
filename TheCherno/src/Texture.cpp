#include "Texture.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: m_filePath(path)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	// What method to use to DOWN scale the image
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	// What method to use to UP scale the image
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// How to deal with wrapping. Clamp, tile, ect.
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0,
		// INTERNAL format (modern openGL asks for the bit depth, not just channels)
		GL_RGBA8,
		m_width, m_height,  // self explanatory
		0, // border
		GL_RGBA, // the actual format of the data
		GL_UNSIGNED_BYTE,
		// pointer to the data. Can be nullptr bc the width, height and internal format
		// already specify how much memory will be needed --> allocates memory on the GPU.
		m_localBuffer
	));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::bind(unsigned int slot /*= 0*/) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
