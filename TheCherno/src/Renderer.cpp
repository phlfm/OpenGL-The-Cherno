#include "Renderer.h"

#include <iostream>

void
GL_clear_error()
{
    unsigned int error_counter = 0;
    while (glGetError() != GL_NO_ERROR)
    {
        ++error_counter;
    }
    if (error_counter > 0)
    {
        std::cout << "GL_clear_error cleared " << error_counter
                  << " errors." << std::endl;
    }
}

bool
GL_log_call(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error << ") on " << function
            << " in " << file << "@" << line << std::endl;
        return false;
    }
    return true;
}