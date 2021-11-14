#pragma once
#ifndef H_RENDERER
#define H_RENDERER

#include <GL/glew.h>
#include <assert.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// __debugbreak is MSVC specific.
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GL_clear_error();\
                  x;\
                  ASSERT(GL_log_call(#x, __FILE__, __LINE__))

void
GL_clear_error();

bool
GL_log_call(const char *function, const char *file, int line);


class Renderer
{
public:
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
    void Clear() const;
private:
};

#endif // H_RENDERER