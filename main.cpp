#include "controller/GameController.hpp"

#include <iostream>

#define WINDOW_WIDTH 1300
#define WINDOW_HEIGTH 700
#define TARGET_FPS 60

using namespace ramboindustries::controller;
using namespace std;


int main(int argc, char ** argv) 
{

    GameType play_mode = GameType::CPU_VS_CPU;

    if (argc > 1)
    {
        const auto option = string(argv[1]);

        if ("player-vs-cpu" == option)
        {
            play_mode = GameType::PLAYER_VS_CPU;
        }
        else if ("cpu-vs-player" == option)
        {
            play_mode = GameType::CPU_VS_PLAYER;
        }
        else if ("player-vs-player" == option)
        {
            play_mode = GameType::PLAYER_VS_PLAYER;
        }
        else if ("cpu-vs-cpu" == option)
        {
            play_mode = GameType::CPU_VS_CPU;
        }
        else 
        {
            cerr << "Play mode: " << argv[1] << " is invalid ... Falling back to cpu-vs-cpu" << endl;
            play_mode = GameType::CPU_VS_CPU;
        }
    }

    Game game(
        WINDOW_HEIGTH,
        WINDOW_WIDTH,
        TARGET_FPS,
        play_mode
    );

    game.run();

    return 0;
}