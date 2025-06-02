#include "platform.h"
#include "Game.h"

int main(int argc, char** argv) {
    Game* game = Game::getInstance();

    game->init(argc, argv);

    game->run();
    
    return 0;
}
