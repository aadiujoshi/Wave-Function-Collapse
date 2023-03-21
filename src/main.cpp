#include "GL/glew.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <chrono>

#include "header_paths.h"
#include renderer_h
#include vertex_buffer_h
#include vertex_array_h
#include index_buffer_h
#include shader_h
#include texture_h

#define ARRLENGTH(arr, type) sizeof(arr)/sizeof(type)
#define uint unsigned int
#define timeNs() std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count()

int main() {
    {
        GLFWwindow* window;

        //-----------------------------------init-----------------------------------------
        //-----------------------------------init-----------------------------------------
        //-----------------------------------init-----------------------------------------

        if (!glfwInit())
            return -2;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(1920, 1080, "window", NULL, NULL);
        if (!window) {
            glfwTerminate();
            return -3;
        }

        glfwMakeContextCurrent(window);

        GLenum ini = glewInit();

        if (ini != GLEW_OK) {
            std::cout << " glew fail code: " << ini << "\n";
            return -10;
        }

        //glfwSwapInterval(1);

        std::cout << "opengl version: " << glGetString(GL_VERSION) << "\n";
        //-------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------

        float rect_vertex[] = {
            0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 1.0f, 0.0,
            -0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f
        };

        uint rect_indices[] = {
            0, 1, 3, 0, 2, 3
        };

        glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        glCall(glEnable(GL_BLEND));

        graphics::vertex_array vao;
        graphics::vertex_buffer vbo(rect_vertex, sizeof(rect_vertex));
        vbo.add_layout({ GL_FLOAT, 2, GL_FALSE });
        vbo.add_layout({ GL_FLOAT, 2, GL_FALSE });
        vao.add_buffer(vbo);
        graphics::index_buffer ibo(rect_indices, ARRLENGTH(rect_indices, uint));
        graphics::renderer renderer;

        graphics::shader shader("shader/generic_shader");
        graphics::texture texture("resources/testing.png");
        texture.bind();
        shader.set_1i("u_texture", 0);

        UNBIND_ALL();

        vao.bind();
        ibo.bind();

        while (!glfwWindowShouldClose(window)) {
            long long startNano = timeNs();

            renderer.clear();

            /*shader.set_4f("u_color", (float)(rand() / (RAND_MAX * 1.0f)),
                (float)(rand() / (RAND_MAX * 1.0f)),
                (float)(rand() / (RAND_MAX * 1.0f)), 1);*/

            renderer.draw(vao, ibo, shader);

            glfwSwapBuffers(window);

            glfwPollEvents();   

            std::string frames = std::string("wavefunction collapse || fps: ") + std::to_string(0x3B9ACA00 / (timeNs() - startNano));

            glfwSetWindowTitle(window, frames.c_str());
        }
    }

    // Clean up
    glfwTerminate();

    return 0;
}