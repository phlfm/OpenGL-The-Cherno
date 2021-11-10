#pragma once
#ifndef H_RENDERER
#define H_RENDERER

#include <GL/glew.h>
#include <assert.h>

// __debugbreak is MSVC specific.
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GL_clear_error();\
                  x;\
                  ASSERT(GL_log_call(#x, __FILE__, __LINE__))

void
GL_clear_error();

bool
GL_log_call(const char* function, const char* file, int line);

#endif // H_RENDERER