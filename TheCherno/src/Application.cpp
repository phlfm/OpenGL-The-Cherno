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

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


int
main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window{ glfwCreateWindow(566, 555, "Hello World", NULL, NULL) };
    if (!window)
    {
        glfwTerminate();
        return -2;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Glew Init error!" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    {

        GLCall(glEnable(GL_BLEND)); 
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
            +0.5f, -0.5f, 1.0f, 0.0f, // 1
            +0.5f, +0.5f, 1.0f, 1.0f, // 2
            -0.5f, +0.5f, 0.0f, 1.0f // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va{};
        // sizeof(positions) could be len(positions) * 4 * sizeof(float)
        VertexBuffer vb{ positions, 4 * 4 * sizeof(float) };

        VertexBufferLayout layout{};
        layout.push<float>(2);
        layout.push<float>(2);
        va.add_buffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/basic");
        
        Renderer renderer;

        Texture texture("res/textures/pikachu.png");
        unsigned int texture_slot{ 0 };
        texture.bind(texture_slot);

        shader.bind();
        shader.setUniform1i("u_texture", texture_slot);
        
        // Unbind all
        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();

        float multiplier = 1.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            renderer.Draw(va, ib, shader);

            // Later we'll abstract this uniform setting into materials
            shader.bind();
            //shader.setUniform4f("u_color", { 0.4f * multiplier, 0.1f * multiplier, 0.7f * multiplier, 1.0f });
            //multiplier -= increment;
            //if (multiplier < 0.3f) {
            //    increment = -increment;
            //}
            //else if (multiplier >= 1.0f) {
            //    increment = -increment;
            //}

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}