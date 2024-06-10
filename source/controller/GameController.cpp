#include "controller/GameController.hpp"

#include <iostream>
#include <raylib.h>

#include "controller/PhysicController.hpp"
#include "object/AIPaddle.hpp"
#include "object/UserPaddle.hpp"
#include "shape/Shape.hpp"

using namespace ramboindustries;
using namespace component;
using namespace object;
using namespace controller;

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
    left_score(width / 4 - 20, 20),
    right_score(3 * width / 4 - 20, 20),
    ball({(float) width / 2, (float) height / 2}, 20.0)
{
    InitWindow(width, height, "Pong Game");
    SetTargetFPS(target_fps);

    InitAudioDevice();
    goal_sound = LoadSound("./assets/powerUp.wav");
    bounce_sound = LoadSound("./assets/bounce.mp3");

    // 3% of total width
    const int paddle_width = width * 0.03;

    // 20% of total heigth
    const int paddle_height = height * 0.20;

    switch (game_type) 
    {
        case GameType::CPU_VS_CPU:
        {
            auto l_paddle = new AIPaddle(ball, PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new AIPaddle(ball, PaddleSide::RIGHT, paddle_width, paddle_height);

            update_componenets.push_back(l_paddle);
            update_componenets.push_back(r_paddle);

            left_paddle = unique_ptr<AIPaddle>(l_paddle);
            right_paddle = unique_ptr<AIPaddle>(r_paddle);
            break;
        }

        case GameType::CPU_VS_PLAYER:
        {
            auto l_paddle = new AIPaddle(ball, PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new UserPaddle(PaddleSide::RIGHT, paddle_width, paddle_height);

            update_componenets.push_back(l_paddle);
            update_componenets.push_back(r_paddle);

            input_components.push_back(r_paddle);

            left_paddle = unique_ptr<AIPaddle>(l_paddle);
            right_paddle = unique_ptr<Paddle>(r_paddle);
            break;
        }
        case GameType::PLAYER_VS_CPU:
        {
            auto l_paddle = new UserPaddle(PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new AIPaddle(ball, PaddleSide::RIGHT, paddle_width, paddle_height);

            input_components.push_back(l_paddle);

            update_componenets.push_back(l_paddle);
            update_componenets.push_back(r_paddle);

            left_paddle = unique_ptr<Paddle>(l_paddle);
            right_paddle = unique_ptr<AIPaddle>(r_paddle);
            break;
        }
        case GameType::PLAYER_VS_PLAYER:
        {
            auto l_paddle = new UserPaddle(PaddleSide::LEFT, paddle_width, paddle_height);
            auto r_paddle = new UserPaddle(PaddleSide::RIGHT, paddle_width, paddle_height);

            input_components.push_back(l_paddle);
            input_components.push_back(r_paddle);

            update_componenets.push_back(l_paddle);
            update_componenets.push_back(r_paddle);

            left_paddle = unique_ptr<Paddle>(l_paddle);
            right_paddle = unique_ptr<Paddle>(r_paddle);
            break;             
        }
    }

    update_componenets.push_back(&ball);

    render_componenets.push_back(&ball);
    render_componenets.push_back(left_paddle.get());
    render_componenets.push_back(right_paddle.get());
    render_componenets.push_back(&middle_wall);

    render_componenets.push_back(&left_score);
    render_componenets.push_back(&right_score);

}

Game::~Game()
{
    UnloadSound(goal_sound);
    UnloadSound(bounce_sound);
    CloseAudioDevice();
    CloseWindow();    
}

void Game::run()
{
    do 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        input_phase();
        update_phase();
        render_phase();

        EndDrawing();
    } while(!WindowShouldClose());
}

void Game::input_phase() 
{
    for (auto& inputable : input_components)
    {
        inputable->input();
    }
}

void Game::update_phase() 
{
    const float delta_time = GetFrameTime();
    for (auto& updatable : update_componenets)
    {
        updatable->update(delta_time);
    }
    handle_paddle_collissions();
    handle_ball_collissions();
}

void Game::render_phase() const
{
    for (auto& drawable : render_componenets)
    {
        drawable->render();
    }
}

void Game::handle_paddle_collissions() 
{
    const shape::Shape& left_paddle = *(this->left_paddle.get());
    const shape::Shape& right_paddle = *(this->right_paddle.get());


    if (insersect_one_of(left_paddle, this->top_wall, this->bottom_wall)) 
    {
        this->left_paddle->limit();
    }

    if (insersect_one_of(right_paddle, this->top_wall, this->bottom_wall))
    {
        this->right_paddle->limit();
    }
}

void Game::handle_ball_collissions()
{
    
    const shape::Shape& left_paddle = *(this->left_paddle.get());
    const shape::Shape& right_paddle = *(this->right_paddle.get());

    if (insersect_one_of(this->ball, left_paddle, right_paddle))
    {
        this->ball.reverse_x();
        PlaySound(this->bounce_sound);
    }

    if (insersect_one_of(this->ball, this->top_wall, this->bottom_wall))
    {
        this->ball.reverse_y();
        PlaySound(this->bounce_sound);
    }

    if (intersect(this->ball, this->left_wall))
    {
        this->right_score += 1;
        this->ball.recenter();
        PlaySound(this->goal_sound);
    }
    else if (intersect(this->ball, this->right_wall))
    {
        this->left_score += 1;
        this->ball.recenter();
        PlaySound(this->goal_sound);
    }



}