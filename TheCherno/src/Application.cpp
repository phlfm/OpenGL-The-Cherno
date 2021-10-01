/*

References:
    The Cherno YouTube channel https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw
    The Cherno OpenGL playlist https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
    OpenGL documentation https://docs.gl/
*/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <assert.h>
#include <iostream>
#include <fstream>

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

static unsigned int
compile_shader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // alloca allocates dynamically on the STACK!
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader "
            << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << std::endl << message << std::endl << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int
create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
    assert(vs != 0);
    assert(fs != 0);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int
main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Glew Init error!" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    unsigned int buffer = 0;
    unsigned int shader = 0;
    {
        float positions[] = {
            -0.5f, -0.5f,
            +0.5f, -0.5f,
            +0.5f, +0.5f,
            -0.5f, +0.5f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // generate 1 buffer and assign it an id
        glGenBuffers(1, &buffer);
        // select the buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        // specify size in bytes. Could be sizeof(positions) and pass it data
        glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

        // Tell OpenGL how to interpret the buffer
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);

        unsigned int ibo = 0;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        std::string vertex_shader = read_text_file("res/shaders/basic_vertex.glsl");
        std::string fragment_shader = read_text_file("res/shaders/basic_fragment.glsl");
        shader = create_shader(vertex_shader, fragment_shader);
        glUseProgram(shader);
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // How does OpenGL know what arrays to draw?
        // It knows because OpenGL is a state machine!
        // We told it what to draw with glBindBuffer.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}