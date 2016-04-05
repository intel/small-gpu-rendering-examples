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

#include <string.h>
#include <iostream>
#include <GL/glu.h>

#include "error.h"

void printGlErrors_(const char* where, const int line) {
    GLenum error = GL_NO_ERROR;
    do {
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "[ERROR] OpenGL ";
            if (strlen(where) > 0)
                std::cerr << "(" << where << ":" << line << ") ";
            std::cerr << gluErrorString(error) << std::endl;
        }
    } while (error != GL_NO_ERROR);
}
