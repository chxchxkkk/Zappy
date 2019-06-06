#include <iostream>
#include "Game.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
        return (84);
    try {
        Game game(argc, argv);
        game.run();
        std::cout << "run end" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << "ERROR" << std::endl;
    }
    std::cout << "leaving" << std::endl;
    return (0);
}
