/*

References:
    The Cherno YouTube channel https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw
    The Cherno OpenGL playlist https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
    OpenGL documentation https://docs.gl/
*/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
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

    {
        float positions[6] = {
            -0.5f, -0.5f,
            +0.0f, +0.5f,
            +0.5f, -0.5f
        };

        unsigned int buffer;
        // generate 1 buffer and assign it an id
        glGenBuffers(1, &buffer);
        // select the buffer
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        // specify size in bytes. Could be sizeof(positions) and pass it data
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

        // Tell OpenGL how to interpret the buffer
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // How does OpenGL know what arrays to draw?
        // It knows because OpenGL is a state machine!
        // We told it what to draw with glBindBuffer.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}