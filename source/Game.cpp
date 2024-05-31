#include "pong/Game.hpp"
#include "pong/Ball.hpp"
#include "pong/Paddle.hpp"

#include <memory>
#include <raylib.h>
#include <iostream>

using namespace ramboindustries;
using namespace std;


Game::Game(
    unsigned int height, 
    unsigned int width,
    unsigned int target_fps,
    const GameType game_type
)
:
    left_wall({0, 0, 0, (float)height}),
    right_wall({(float) width, 0, 0, (float)height}),
    top_wall({0, 0, (float) width, 0}),
    bottom_wall({0, (float) height, (float) width, 0}),
    middle_wall({(float) width / 2, 0, 5, (float) height}),
    goal_sound(LoadSound("./assets/powerUp.wav")),
    left_score(0),
    rigth_score(0),
    ball(20.0)
{

    ball.center = {(float) width / 2, (float) height / 2};

    InitWindow(width, height, "Pong Game");
    SetTargetFPS(target_fps);

    // 3% of total width
    const int paddle_width = width * 0.03;

    // 20% of total heigth
    const int paddle_height = height * 0.20;

    switch (game_type) 
    {
        case GameType::CPU_VS_CPU:
        {
            auto l_paddle = new AIPaddle(ball, PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new AIPaddle(ball, PaddleSide::RIGTH, paddle_width, paddle_height);

            updatable_componenets.push_back(l_paddle);
            updatable_componenets.push_back(r_paddle);

            left_paddle = unique_ptr<AIPaddle>(l_paddle);
            right_paddle = unique_ptr<AIPaddle>(r_paddle);
            break;
        }

        case GameType::CPU_VS_PLAYER:
        {
            auto l_paddle = new AIPaddle(ball, PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new Paddle(PaddleSide::RIGTH, paddle_width, paddle_height);

            updatable_componenets.push_back(l_paddle);
            updatable_componenets.push_back(r_paddle);

            inputable_components.push_back(r_paddle);

            left_paddle = unique_ptr<AIPaddle>(l_paddle);
            right_paddle = unique_ptr<Paddle>(r_paddle);
            break;
        }
        case GameType::PLAYER_VS_CPU:
        {
            auto l_paddle = new Paddle(PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new AIPaddle(ball, PaddleSide::RIGTH, paddle_width, paddle_height);

            inputable_components.push_back(l_paddle);

            updatable_componenets.push_back(l_paddle);
            updatable_componenets.push_back(r_paddle);

            left_paddle = unique_ptr<Paddle>(l_paddle);
            right_paddle = unique_ptr<AIPaddle>(r_paddle);
            break;
            break;
        }
        case GameType::PLAYER_VS_PLAYER:
        {
            auto l_paddle = new Paddle(PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new Paddle(PaddleSide::RIGTH, paddle_width, paddle_height);

            inputable_components.push_back(l_paddle);
            inputable_components.push_back(r_paddle);

            updatable_componenets.push_back(l_paddle);
            updatable_componenets.push_back(r_paddle);

            left_paddle = unique_ptr<Paddle>(l_paddle);
            right_paddle = unique_ptr<Paddle>(r_paddle);
            break;             
            break;        
        }
    }

    updatable_componenets.push_back(&ball);

    drawnable_componenets.push_back(&ball);
    drawnable_componenets.push_back(left_paddle.get());
    drawnable_componenets.push_back(right_paddle.get());
    drawnable_componenets.push_back(&middle_wall);
}

Game::~Game()
{
    UnloadSound(goal_sound);
    CloseAudioDevice();
    CloseWindow();    
}


void Game::input_phase() 
{
    for (auto& inputable : inputable_components)
    {
        inputable->input();
    }
}

void Game::update_phase() 
{
    const float delta_time = GetFrameTime();
    for (auto& updatable : updatable_componenets)
    {
        updatable->update(delta_time);
    }

    handle_paddle_collissions();
    handle_ball_collissions();
}

void Game::draw_phase() const
{
    for (auto& drawable : drawnable_componenets)
    {
        drawable->draw();
    }

    const float left_position = (float) GetScreenWidth() / 4 - 20;
    const float right_position = 3 * (float) GetScreenWidth()  / 4 - 20;
    const int font_size = 30;

    DrawText(TextFormat("%i", left_score),  left_position, 20, font_size, RED);
    DrawText(TextFormat("%i", rigth_score), right_position, 20, font_size, RED);
}

void Game::run()
{
    do 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        input_phase();
        update_phase();
        draw_phase();

        EndDrawing();
    } while(!WindowShouldClose());

}

void Game::handle_paddle_collissions()
{
    if (left_paddle->intersect(&top_wall) || left_paddle->intersect(&bottom_wall))
    {
        left_paddle->limit();
    }
    
    if (right_paddle->intersect(&top_wall) || right_paddle->intersect(&bottom_wall))
    {
        right_paddle->limit();
    }
}

void Game::handle_ball_collissions()
{

    if (ball.intersect(left_paddle.get()) || ball.intersect(right_paddle.get()))
    {
        ball.reverse_x();
    }

    if (ball.intersect(&top_wall) || ball.intersect(&bottom_wall)) 
    {
        ball.reverse_y();
    }

    if (ball.intersect(&left_wall))
    {
        rigth_score++;
        ball.recenter();
        PlaySound(goal_sound);
    }

    if (ball.intersect(&right_wall))
    {
        left_score++;
        ball.recenter();
        PlaySound(goal_sound);        
    }

}