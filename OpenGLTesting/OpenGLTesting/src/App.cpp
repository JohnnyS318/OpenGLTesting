  #include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

  int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World of OpenGl.", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

	if(glewInit() != GLEW_OK)
		std::cout << "Glew not ok" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f,
        };

        unsigned int indicies[] = {
            0,1,2,
            2,3,0
        };
    	
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

		IndexBuffer ib(indicies, 6);

        Shader shader("res/shaders/basic.shader");
        shader.Bind();
        const char* colorName= "u_Color";
    	shader.SetUniform4f(colorName, 0.8F, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/logo.jpg");
        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
    	
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
    	
        float r = 0.0f;
        float increment = 0.05f;

        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            shader.Bind();
        	
            renderer.Draw(va, ib, shader);

            if (r > 1.0f) {
                increment = -0.05f;
            }
            else if (r <= 0.0f)
                increment = 0.05f;
            r += increment;

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        colorName = nullptr;
        delete colorName;
    	
    }
    glfwTerminate();
    return 0;
}
