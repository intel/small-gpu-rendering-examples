// Copyright (c) 2017 Intel Corporation
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

#include "other.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include "error.h"
#include "io.h"

// should be defined in CMakeLists.txt
#ifndef SHADERS_DIR
#define SHADERS_DIR "./"
#endif

void initGlew() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    // ignore "invalid enumerant" error, it's a known bug
    // https://www.opengl.org/wiki/OpenGL_Loading_Library
    GLenum error = glGetError();
    if (error != GL_INVALID_ENUM && error != GL_NO_ERROR) {
        printf("[ERROR] OpenGL ");
        printf("%s\n", gluErrorString(error));
        printGlErrors();
        throw Exception("glewInit failed due to OpenGL errors");
    }
    if(err != GLEW_OK) {
        throw Exception("glewInit failed");
    }
}

GLuint compileShader(const std::string& filepath, ShaderType type) {
    std::string source = readFile(SHADERS_DIR + filepath);
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
