#include <iostream>
#include "Game.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
        return (84);
    try {
        Game game(argc, argv);
        game.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
