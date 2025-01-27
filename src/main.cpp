#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "World.h"
#include <iostream>
#include <vector>
#include <cstdlib>  // For generating random numbers
#include <ctime>    // For initializing random seed

// Helper function: Compute the highest point (y + radius) of all rigid bodies in the world
static float computeMaxTopOfAllBalls(const World &world) {
    float maxTop = 0.0f;
    size_t count = world.getBodiesCount();
    for (size_t i = 0; i < count; i++) {
        const RigidBody* body = world.getBodyPtr(i);
        float topY = body->position.y + body->radius;
        if (topY > maxTop) {
            maxTop = topY;
        }
    }
    return maxTop;
}

// Initialize SDL and OpenGL context
bool initSDL(SDL_Window** window, SDL_GLContext* context, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow("RigidBody AABB Demo",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width, height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!*window) {
        std::cerr << "Failed to create SDL window.\n";
        return false;
    }

    *context = SDL_GL_CreateContext(*window);
    if (!*context) {
        std::cerr << "Failed to create OpenGL context.\n";
        return false;
    }

    SDL_GL_SetSwapInterval(1); // Enable V-Sync
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW.\n";
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    return true;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    int WIDTH = 800, HEIGHT = 600;

    if (!initSDL(&window, &glContext, WIDTH, HEIGHT)) {
        return -1;
    }

    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create the world
    World world;

    // Add two rigid bodies to the world
    {
        auto body1 = std::make_unique<RigidBody>();
        body1->position = glm::vec3(-5.0f, 10.0f, 0.0f);
        body1->radius = 1.0f;
        body1->mass = 1.0f;
        world.addRigidBody(std::move(body1));
    }
    {
        auto body2 = std::make_unique<RigidBody>();
        body2->position = glm::vec3(5.0f, 15.0f, 0.0f);
        body2->radius = 1.0f;
        body2->mass = 2.0f;
        world.addRigidBody(std::move(body2));
    }

    // Set up the camera view matrix
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 20.0f, 60.0f),  // Camera position (higher and farther)
        glm::vec3(0.0f, 3.0f, 0.0f),   // Looking towards (0, 3, 0)
        glm::vec3(0.0f, 1.0f, 0.0f)    // Up direction
    );

    // Set up the projection matrix
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),
        0.1f, 200.0f
    );

    bool running = true;
    SDL_Event event;
    float deltaTime = 0.016f; // ~16ms per frame

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {

                    case SDLK_SPACE: {
                        // 1) Calculate the highest point of all balls in the world
                        float maxTop = computeMaxTopOfAllBalls(world);

                        // 2) Generate random x and z positions
                        float rx = -20.f + 40.f * (rand() / (float)RAND_MAX);  // Random x [-20, +20]
                        float rz = -20.f + 40.f * (rand() / (float)RAND_MAX);  // Random z [-20, +20]

                        // 3) Create a new rigid body at (rx, maxTop+10, rz)
                        auto body = std::make_unique<RigidBody>();
                        body->radius = 1.0f;
                        body->mass = 1.0f;
                        body->position = glm::vec3(rx, maxTop + 10.0f, rz);

                        float vx = -5.f + 10.f * (rand() / (float)RAND_MAX);  // Random x velocity
                        float vy = -2.f;  // Downward velocity
                        float vz = -5.f + 10.f * (rand() / (float)RAND_MAX);  // Random z velocity
                        body->velocity = glm::vec3(vx, vy, vz);

                        world.addRigidBody(std::move(body));
                        std::cout << "[User] Added a new rigid body at ("
                                  << rx << ", " << (maxTop + 10.f) << ", " << rz
                                  << "), velocity= (" << vx << "," << vy << "," << vz << ")\n";
                    } break;

                    case SDLK_d: {
                        // Print the distance of all rigid bodies to the ground
                        size_t count = world.getBodiesCount();
                        for (size_t i = 0; i < count; ++i) {
                            float dist = world.getDistanceToGround(i);
                            std::cout << "Body " << i << " distance to ground = " << dist << std::endl;
                        }
                    } break;

                    default: break;
                }
            }
        }

        // Simulate physics
        world.simulate(deltaTime);

        // Clear the screen and depth buffer
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the world
        world.render(view, projection);

        // Swap the window buffers
        SDL_GL_SwapWindow(window);
    }

    // Clean up and exit
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
