#include "pong/Game.hpp"

#define WINDOW_WIDTH 1300
#define WINDOW_HEIGTH 700
#define TARGET_FPS 60

using namespace ramboindustries;

int main(int argc, char ** argv) 
{
    Game game(
        WINDOW_HEIGTH,
        WINDOW_WIDTH,
        TARGET_FPS,
        GameType::CPU_VS_CPU
    );

    game.run();

    return 0;
}