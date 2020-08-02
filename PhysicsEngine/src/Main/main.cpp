#include "Game.h"
#include <iostream>


int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    game.run();
    return 0;
}
