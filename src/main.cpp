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

        window = glfwCreateWindow(600, 600, "test window", NULL, NULL);
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

        float tri_pos[] = {
            0.5f, 0.5f,
            0.5f, -0.5f,
            -0.5f, 0.5f,
            -0.5f, -0.5f,
        };

        uint rect_indices[] = {
            0, 1, 3, 0, 2, 3
        };

        graphics::vertex_array vao;

        graphics::vertex_buffer vbo(tri_pos, sizeof(tri_pos));
        vbo.add_layout({ GL_FLOAT, 2, GL_FALSE });

        vao.add_buffer(vbo);

        graphics::index_buffer ibo(rect_indices, ARRLENGTH(rect_indices, uint));

        graphics::shader g_shader("shader/generic_shader");

        graphics::renderer renderer;

        UNBIND_ALL();

        vao.bind();
        ibo.bind();

        while (!glfwWindowShouldClose(window)) {
            long long startNano = timeNs();

            g_shader.set_4f("u_color", (float)(rand() / (RAND_MAX * 1.0f)),
                (float)(rand() / (RAND_MAX * 1.0f)),
                (float)(rand() / (RAND_MAX * 1.0f)), 1);

            renderer.draw(vao, ibo, g_shader);

            glfwSwapBuffers(window);

            glfwPollEvents();

            std::string frames = std::string("fps: ") + std::to_string(0x3B9ACA00 / (timeNs() - startNano));

            glfwSetWindowTitle(window, frames.c_str());
        }
    }

    // Clean up
    glfwTerminate();

    return 0;
}


namespace util {
    void glClearErrors() {
        while (glGetError() != GL_NO_ERROR);
    }

    bool glCheckErrors(const char* func, const char* file, int line) {

        while (GLenum err = glGetError()) {
            std::cout << "opengl error: " << err << " at : " << func << " line " << line << " in " << file << std::endl;
            return false;
        }

        return true;
    }

    std::string readFile(std::string fname) {
        std::ifstream file(fname);
        if (!file.is_open()) {
            std::cout << "failed to open file" << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        //std::cout << buffer.str();
        return buffer.str();
    }
}
