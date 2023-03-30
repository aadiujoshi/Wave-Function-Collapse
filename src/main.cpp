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

static long long i;

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

        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        const int screen_width = mode->width;
        const int screen_height = mode->height;

        std::cout << "Screen resolution: " << screen_width << "x" << screen_height << std::endl;

        window = glfwCreateWindow(screen_width, screen_height, "window", NULL, NULL);
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


        const float _offset_x_1 = -0.5f;
        const float _sq_size_1 = 0.3f;
        float sample_va[] = {
            _sq_size_1 + _offset_x_1, _sq_size_1, 1.0f, 1.0f,
            _sq_size_1 + _offset_x_1, -_sq_size_1, 1.0f, 0.0,
            -_sq_size_1 + _offset_x_1, _sq_size_1, 0.0f, 1.0f,
            -_sq_size_1 + _offset_x_1, -_sq_size_1, 0.0f, 0.0f
        };

        const float _offset_x_2 = 0.5f;
        const float _sq_size_2 = 0.3f;
        float output_va[] = {
            _sq_size_2 + _offset_x_2, _sq_size_2, 1.0f, 1.0f,
            _sq_size_2 + _offset_x_2, -_sq_size_2, 1.0f, 0.0,
            -_sq_size_2 + _offset_x_2, _sq_size_2, 0.0f, 1.0f,
            -_sq_size_2 + _offset_x_2, -_sq_size_2, 0.0f, 0.0f
        };

        uint rect_indices[] = {
            0, 1, 3, 0, 2, 3
        };

        glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        glCall(glEnable(GL_BLEND));

        //input texture stuff
        graphics::vertex_array vao;
        graphics::vertex_buffer vbo(sample_va, sizeof(sample_va));
        vbo.add_layout({ GL_FLOAT, 2, GL_FALSE });
        vbo.add_layout({ GL_FLOAT, 2, GL_FALSE });
        vao.add_buffer(vbo);

        //output texture stuff
        graphics::vertex_array vao_out;
        graphics::vertex_buffer vbo_out(output_va, sizeof(output_va));
        vbo_out.add_layout({ GL_FLOAT, 2, GL_FALSE });
        vbo_out.add_layout({ GL_FLOAT, 2, GL_FALSE });
        vao_out.add_buffer(vbo_out);

        graphics::index_buffer ibo(rect_indices, ARRLENGTH(rect_indices, uint));
        graphics::renderer renderer;
        graphics::shader shader("shader/generic_shader");

        graphics::texture texture("C:/Users/aadiu/Desktop/Programming Files/Personal Projects/Java Projects/Summit Game/Summit/resources/sprites/apple-item.png");
        graphics::texture output(400, 400);

        shader.set_1i("u_texture", 0);

        UNBIND_ALL();

        vao.bind();
        ibo.bind();

        while (!glfwWindowShouldClose(window)) {
            long long startNano = timeNs();

            renderer.clear();

            texture.bind();
            renderer.draw(vao, ibo, shader);

            output.bind();
            renderer.draw(vao_out, ibo, shader);

            //uint ind_r = (1.0f * rand() / RAND_MAX) * output.get_width() * output.get_height();

            //std::cout << "x: " << (uint)(ind_r % output.get_width()) << " y: " << (uint)(ind_r / output.get_width()) << std::endl;

            //output.set_rgba((uint)(ind_r % output.get_width()), (uint)(ind_r / output.get_width()), 0, 255, 0, 255);

            //output.set_rgba(0, 0, 0, 0, 0, 0);


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