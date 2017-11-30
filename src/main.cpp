#include <iostream>
#include "display.h"
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "asteroids_game.h"

const int WIDTH = 1024;
const int HEIGHT = 768;

int main(int argc, char const *argv[]) {

    bool is_running = true;
    SDL_Event event;

    Display display(WIDTH, HEIGHT, "Asteroids");
    AsteroidsGame game(display);

    while (is_running) {
        // Poll SDL events
        while (SDL_PollEvent(&event)) {
            // Handle quit event
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
            // Handle Input
            else {
                game.input(event);
            }
        }
        // Update game state and draw
        game.update(display.getFrameDelta());
        game.draw();
    }

    return 0;
}
