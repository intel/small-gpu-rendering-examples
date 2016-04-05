/* Copyright 2015 Martina Kollarova
 *
 * Reproducer for Mesa bug https://bugs.freedesktop.org/show_bug.cgi?id=90821
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// Try creating an EGL context, either surface-less or with a pbuffer. Doesn't
// show anything, just prints GL info and "Success!" on stdout.
// Can be compiled by itself with:
//     gcc main.cpp -std=c++11 -lEGL -lGLESv2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

// set this to false if you want to use a pbuffer which doesn't segfault
#ifndef NO_SURFACE
#define NO_SURFACE true
#endif

// used the same way as printf
#define fail(...) { fprintf(stderr, "[ERROR] (%s:%d) ", __FILE__, __LINE__); \
                    fprintf(stderr, __VA_ARGS__); \
                    fprintf(stderr, "\n"); \
                    exit(1); }

const char* getEGLErrorString(EGLint error) {
  switch (error) {
    case EGL_SUCCESS:
      return "EGL_SUCCESS";
    case EGL_BAD_ACCESS:
      return "EGL_BAD_ACCESS";
    case EGL_BAD_ALLOC:
      return "EGL_BAD_ALLOC";
    case EGL_BAD_ATTRIBUTE:
      return "EGL_BAD_ATTRIBUTE";
    case EGL_BAD_CONTEXT:
      return "EGL_BAD_CONTEXT";
    case EGL_BAD_CONFIG:
      return "EGL_BAD_CONFIG";
    case EGL_BAD_CURRENT_SURFACE:
      return "EGL_BAD_CURRENT_SURFACE";
    case EGL_BAD_DISPLAY:
      return "EGL_BAD_DISPLAY";
    case EGL_BAD_SURFACE:
      return "EGL_BAD_SURFACE";
    case EGL_BAD_MATCH:
      return "EGL_BAD_MATCH";
    case EGL_BAD_PARAMETER:
      return "EGL_BAD_PARAMETER";
    case EGL_BAD_NATIVE_PIXMAP:
      return "EGL_BAD_NATIVE_PIXMAP";
    case EGL_BAD_NATIVE_WINDOW:
      return "EGL_BAD_NATIVE_WINDOW";
    default:
      return "UNKNOWN";
  }
}

void printEGLErrors() {
    EGLint error = EGL_SUCCESS;
    do {
        error = eglGetError();
        if (error != EGL_SUCCESS) {
            printf("[ERROR] %s\n", getEGLErrorString(error));
        }
    } while (error != EGL_SUCCESS);
}

void printEGLInfo(EGLDisplay display) {
    const char *s;
    s = eglQueryString(display, EGL_VERSION);
    printf("EGL_VERSION = %s\n", s);
    s = eglQueryString(display, EGL_EXTENSIONS);
    printf("EGL_EXTENSIONS = %s\n", s);
}

void printGLInfo() {
    const GLubyte *s;
    s = glGetString(GL_VENDOR);
    printf("GL_VENDOR = %s\n", s);
    s = glGetString(GL_VERSION);
    printf("GL_VERSION = %s\n", s);
    s = glGetString(GL_RENDERER);
    printf("GL_REMDERER = %s\n", s);
    s = glGetString(GL_EXTENSIONS);
    printf("GL_EXTENSIONS = %s\n", s);
}

bool hasExtension(const char *name) {
    auto extensions = reinterpret_cast<const char *>
                                      (glGetString(GL_EXTENSIONS));
    if (extensions == nullptr) fail("couldn't get extension list");
    return strstr(extensions, name) != nullptr;
}

EGLConfig chooseFBConfig(EGLDisplay display) {
    const EGLint visual_attribs[] = {
        EGL_BUFFER_SIZE, 32,
        EGL_ALPHA_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };
    printf("Getting matching framebuffer configs\n");
    EGLint num_configs = 0;
    EGLConfig config[1];
    if (!eglChooseConfig(display, visual_attribs, config, 1, &num_configs)) {
      printEGLErrors();
      fail("eglChooseConfig failed");
    }
    if (num_configs == 0) fail("No FB config found");
    return config[0];
}

EGLSurface createSurface(EGLDisplay display, EGLConfig config) {
    const EGLint surface_attribs[] = {
        EGL_WIDTH, 1,
        EGL_HEIGHT, 1,
        EGL_NONE
    };
    auto surface = eglCreatePbufferSurface(display, config, surface_attribs);
    if (surface == EGL_NO_SURFACE) {
        printEGLErrors();
        fail("Couldn't create surface");
    }
    return surface;
}

EGLContext createContext(EGLDisplay display, EGLConfig config) {
    const EGLint context_attributes[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    auto context = eglCreateContext(display, config, nullptr, context_attributes);
    if (context == EGL_NO_CONTEXT) {
        printEGLErrors();
        fail("EGL context creation failed");
    }
    return context;
}

int main(int argc, char* argv[]) {
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) fail("Failed to open display");
    if (!eglInitialize(display, nullptr, nullptr))
        fail("Failed to initialize EGL");
    printEGLInfo(display);
    printEGLErrors();

    auto config = chooseFBConfig(display);
    auto context = createContext(display, config);
    EGLBoolean res = false;
    if (NO_SURFACE) { // reproduce bug
        res = eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context);
    } else { // everything works fine with a pbuffer
        auto surface = createSurface(display, config);
        res = eglMakeCurrent(display, surface, surface, context);
    }
    if (!res) {
        printEGLErrors();
        fail("Couldn't make context current");
    }
    printGLInfo();
    if (!hasExtension("GL_OES_surfaceless_context"))
      fail("Could not find extension GL_OES_surfaceless_contex");

    glViewport(0, 0, 0, 0); // SEGFAULT?

    eglDestroyContext(display, context);
    eglTerminate(display);
    printf("Success!\n");
    return 0;
}
