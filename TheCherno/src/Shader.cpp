#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include "GL/glew.h"

std::string
read_text_file(const char* path)
{
    std::ifstream file_stream(path);
    file_stream.seekg(0, std::ios::end);
    size_t size = file_stream.tellg();
    std::string buffer(size, ' ');
    file_stream.seekg(0);
    file_stream.read(&buffer[0], size);
    return buffer;
}

unsigned int
Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id{ glCreateShader(type) };
    const char* src{ source.c_str() };
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result{ 0 };
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length = 0;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        // alloca allocates dynamically on the STACK!
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile shader "
            << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << std::endl << message << std::endl << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int
Shader::createShader(const std::string& vertex_shader_code, const std::string& fragment_shader_code)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex_shader_code);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader_code);
    assert(vs != 0);
    assert(fs != 0);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}


Shader::Shader(const std::string& filepath)
	: m_filePath(filepath)
{
    std::string vertex_shader_code = read_text_file((filepath + "_vertex.glsl").c_str());
    std::string fragment_shader_code = read_text_file((filepath + "_fragment.glsl").c_str());
    m_rendererID = createShader(vertex_shader_code, fragment_shader_code);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_rendererID));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_rendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

unsigned int
Shader::GetUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];


    GLCall(int location{ glGetUniformLocation(m_rendererID, name.c_str()) });
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' does not exist!" << std::endl;
    else
        m_uniformLocationCache[name] = location;
    return location;
}

void
Shader::SetUniform4f(const std::string& name, vec4f floats)
{
    GLCall(glUniform4f(GetUniformLocation(name), floats.v0, floats.v1, floats.v2, floats.v3));
}
