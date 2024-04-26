#include <iostream>
#include "game/game.hpp"

int main() {

    srand(static_cast<unsigned>(time(NULL))); // init srand

    Game game = Game();
    game.initialize(); // initialize the game engine 
    game.gameLoop(); // enter game loop

    return 0;
}