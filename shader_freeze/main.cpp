// Copyright (c) 2015 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// This example is mostly a copy of the basic triangle example in 'tutorial/'.
// It uses shaders similar to the ones in the WebGL conformance test
// https://github.com/KhronosGroup/WebGL/blob/master/sdk/tests/conformance/glsl/bugs/temp-expressions-should-not-crash.html
// with 10000 operations, showing a bug in Intel GPU drivers, as described in
// https://bugs.chromium.org/p/chromium/issues/detail?id=593680. The expected
// behavior of this program is a freeze (on Intel GPUs at least). Be warned that
// this might freeze your desktop and you will have to kill this process from
// the tty.
#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "common/error.h"
#include "common/io.h"
#include "common/other.h"

#ifndef SHADERS_DIR
#define SHADERS_DIR "./shaders/"
#endif

const float vertices[] = {
     0.0f,  0.5f,  1.0f, 0.0f, 0.0f, // vertex 1: Red
     0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // vertex 2: Green
    -0.5f, -0.5f,  0.0f, 0.0f, 1.0f  // vertex 3: Blue
};

enum class ShaderType {vertex, fragment};

/**
 * Read |filename| from SHADERS_DIR, compile it as a shader and return its ID.
 */
GLuint compileShader(const std::string& filename, ShaderType type) {
    std::string source = readFile(SHADERS_DIR + filename);
    if (source.length() == 0)
      throw Exception("empty shader file");
    auto gl_type = GL_VERTEX_SHADER;
    if (type != ShaderType::vertex) gl_type = GL_FRAGMENT_SHADER;

    GLuint shader = glCreateShader(gl_type);
    const char* source_c = source.c_str();
    glShaderSource(shader, 1, &source_c, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::cerr << "Failed to compile shader:\n";
        std::cerr << source << std::endl;
        std::cerr << "************************************\n";
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cerr << buffer;
        throw Exception();
    }
    printGlErrors();
    return shader;
}

/**
 * Return ID of the linked and activated shader.
 */
GLuint initShaders() {
    auto vshader = compileShader("vshader.glsl", ShaderType::vertex);
    auto fshader = compileShader("fshader.glsl", ShaderType::fragment);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vshader);
    glAttachShader(shaderProgram, fshader);
    std::cout << "linking shaders" << std::endl;
    glLinkProgram(shaderProgram);
    std::cout << "shaders linked" << std::endl;
    glUseProgram(shaderProgram);
    printGlErrors();
    return shaderProgram;
}

SDL_GLContext initContext(SDL_Window *window) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    printGlErrors();
    return context;
}

/**
 * Copy buffers to memory, set shader attributes, bind to VAO.
 * Return bound VAO ID.
 */
GLuint initBuffers(GLuint shaderProgram) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    printGlErrors();
    return vao;
}

void paint() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    printGlErrors();
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Hello World",
                                           100, 100, 800, 600,
                                           SDL_WINDOW_OPENGL);
    auto context = initContext(window);
    initGlew();
    auto program = initShaders();
    initBuffers(program);

    paint();

    SDL_Event event;
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) break;
            if (event.type == SDL_KEYDOWN) break;
        }
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
