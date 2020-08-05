#include "Game.h"
#include <iostream>


int main(int argc, char** argv) {
    try {
        Game& game = Game::GetInstance();
        game.run();
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    int x;
    std::cin >> x;
    return 0;
}
