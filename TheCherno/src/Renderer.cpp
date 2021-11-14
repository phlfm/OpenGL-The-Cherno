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
GL_log_call(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error << ") on " << function
            << " in " << file << "@" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    shader.bind();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
    /*
    Should we unbind shader / va / ib?
    It *sometimes* is useful for debugging but in release it's just a waste of performance
    */
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
