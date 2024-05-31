#include <iostream>
#include <vector>

#include <raylib.h>

#include "pong/Interface.hpp"
#include "pong/Ball.hpp"
#include "pong/Paddle.hpp"
#include "pong/Wall.hpp"

#define WINDOW_WIDTH 1300
#define WINDOW_HEIGTH 700
#define WINDOW_NAME "Pong Game"
#define TARGET_FPS 60
#define FONT_SIZE 30

using namespace std;
using namespace ramboindustries;

int main(int argc, char ** argv) 
{

    bool two_players = false;

    if (argc > 1 && "two-players" == string(argv[1]))
    {
        cout << "Two Players mode Enable" << endl;
        two_players = true;
    } 
    else 
    {
        cout << "Mode Player vs CPU" << endl; 
    }
    

    cout << "Initializing Game Window" << endl;

    unsigned int left_score = 0;
    unsigned int rigth_score = 0;

    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_NAME);

    InitAudioDevice();

    Sound goalSound = LoadSound("./assets/powerUp.wav");

    SetTargetFPS(TARGET_FPS);
    
    Wall leftWall({0, 0, 0, WINDOW_HEIGTH});
    Wall rightWall({WINDOW_WIDTH, 0, 0, WINDOW_HEIGTH});
    Wall topWall({0, 0, WINDOW_WIDTH, 0});
    Wall bottomWall({0, WINDOW_HEIGTH, WINDOW_WIDTH, 0});

    VisibleWall visibleWall({(float) WINDOW_WIDTH / 2, 0, 5, WINDOW_HEIGTH});

    vector<InputableComponent*> inputables;
    vector<UpdatableComponenet*> updatables;
    vector<DrawnableComponent*> drawnables;

    Ball ball(20.0);

    Paddle right_paddle(false, 25, 120);
    BasePaddle* left_paddle;
    
    if (two_players)
    {
        auto paddle = new Paddle(true, 25, 120);
        inputables.push_back(paddle);
        left_paddle = paddle;
    }
    else 
    {
        left_paddle = new AIPaddle(ball, true, 25, 120);
    }

    inputables.push_back(&right_paddle);

    updatables.push_back(&ball);
    updatables.push_back(left_paddle);
    updatables.push_back(&right_paddle);    

    drawnables.push_back(&ball);
    drawnables.push_back(left_paddle);
    drawnables.push_back(&right_paddle);
    drawnables.push_back(&visibleWall);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        /**
         * Handles the input phase
        */ 
        for (auto& pointer : inputables)
        {
            pointer->input();
        }

        /**
         * Handles the update phase
        */
        const float delta_time = GetFrameTime();

        for (auto& pointer : updatables)
        {
            pointer->update(delta_time);
        }
        
        // Check ball collissions with paddle
        if (ball.intersect(&right_paddle))
        {
            ball.reverse_x();
        }

        if (ball.intersect(left_paddle))
        {
            ball.reverse_x();
        }


        /**
         * Check left & right paddle collissions with top & bottom walls
        */
        if (left_paddle->intersect(&topWall) || left_paddle->intersect(&bottomWall))
        {
            left_paddle->limit();
        }

        if (right_paddle.intersect(&topWall) || right_paddle.intersect(&bottomWall))
        {
            right_paddle.limit();
        }


        // Check ball Collissions with walls
        if (ball.intersect(&leftWall))
        {
            rigth_score++;
            ball.recenter();
            PlaySound(goalSound);
        }

        if (ball.intersect(&rightWall))
        {
            left_score++;
            ball.recenter();
            PlaySound(goalSound);            
        }

        if (ball.intersect(&topWall))
        {
            ball.reverse_y();
        }

        if (ball.intersect(&bottomWall))
        {
            ball.reverse_y();
        }

        /**
         * handles the drawnable phase
        */
        for (auto& pointer : drawnables)
        {
            pointer->draw();
        }

        DrawText(TextFormat("%i", left_score),  WINDOW_WIDTH / 4 - 20, 20, FONT_SIZE, RED);
        DrawText(TextFormat("%i", rigth_score), 3 * WINDOW_WIDTH / 4 - 20, 20, FONT_SIZE, RED);

        EndDrawing();
    }

    delete left_paddle;

    UnloadSound(goalSound);
    CloseAudioDevice();

    CloseWindow();    

    cout << "Finished Game Window" << endl;



    return 0;
}