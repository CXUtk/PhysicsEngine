#include "Game.h"
#include <iostream>
template <typename C>
void print(C& c) {
    typename C::value_type tmp(*c.cbegin());
    printf("%d\n", tmp);
}


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
