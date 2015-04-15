#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

void keyPressHandler(const SDL_Event& event) {
    if (event.type != SDL_KEYDOWN) return;

}


int main(int argc, char *argv[])
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Hello World",
                                           100, 100, 800, 600,
                                           SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
            else keyPressHandler(event);
        }
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
