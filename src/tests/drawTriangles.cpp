#include <iostream>
#include "/Users/tommasob/Desktop/GFXTests/include/SDL2/SDL.h"
#include "/Users/tommasob/Desktop/GFXTests/include/GL/glew.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

SDL_Window *window;
SDL_GLContext gl_context;

bool is_game_running;

void set_sdl_gl_attributes()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource1 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(0.0f, 1.0f, 0.2f, 1.0f);\n"
                                   "}\0";

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL2 initialized successfully." << std::endl;
        set_sdl_gl_attributes();

        window = SDL_CreateWindow("Game", 0, 0, 1024, 768, SDL_WINDOW_OPENGL);
        gl_context = SDL_GL_CreateContext(window);

        if (glewInit() == GLEW_OK)
        {
            std::cout << "GLEW initialization successful" << std::endl;
        }
        else
        {
            std::cout << "GLEW initialization failed" << std::endl;
            return -1;
        }

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
        glCompileShader(fragmentShader1);

        unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
        glCompileShader(fragmentShader2);

        unsigned int shaderProgram1 = glCreateProgram();
        glAttachShader(shaderProgram1, vertexShader);
        glAttachShader(shaderProgram1, fragmentShader1);
        glLinkProgram(shaderProgram1);

        unsigned int shaderProgram2 = glCreateProgram();
        glAttachShader(shaderProgram2, vertexShader);
        glAttachShader(shaderProgram2, fragmentShader2);
        glLinkProgram(shaderProgram2);

        float firstTriangleVerts[] = {
            -0.8f, -0.5f, 0.0f,
            -0.2f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };

        float secondTriangleVerts[] = {
            0.2f, -0.5f, 0.0f,
            0.8f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
        };

        unsigned int VBOs[2], VAOs[2];

        // Generating arrays and buffers for both triangles
        glGenVertexArrays(2, VAOs);
        glGenBuffers(2, VBOs);

        // first triangle setup
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVerts), firstTriangleVerts, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // second triangle setup
        glBindVertexArray(VAOs[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVerts), secondTriangleVerts, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        SDL_Event event;
        is_game_running = true;

        while (is_game_running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        is_game_running = false;
                    }
                }

                if (event.type == SDL_QUIT)
                {
                    is_game_running = false;
                }
            }

            glClearColor(0, 0, 0, 1);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram1);
            glBindVertexArray(VAOs[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glUseProgram(shaderProgram2);
            glBindVertexArray(VAOs[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            SDL_GL_SwapWindow(window);
        }

        glDeleteVertexArrays(2, VAOs);
        glDeleteBuffers(2, VBOs);
        glDeleteProgram(shaderProgram1);
        glDeleteProgram(shaderProgram2);
        SDL_Quit();
    }
    else
    {
        std::cout << "SDL2 initialization failed." << std::endl;
        return -1;
    }

    return 0;
}
