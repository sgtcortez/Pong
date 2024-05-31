#pragma once

#include <raylib.h>
#include <memory>
#include <vector>


#include "pong/Ball.hpp"
#include "pong/Interface.hpp"
#include "pong/Wall.hpp"
#include "pong/Paddle.hpp"

namespace ramboindustries 
{

    enum class GameType 
    {
        CPU_VS_CPU,
        PLAYER_VS_CPU,
        PLAYER_VS_PLAYER,
        CPU_VS_PLAYER,
    };


    /**
     * This is the game structure
    */
    class Game
    {

        private:
            /*const*/ Wall left_wall;
            /*const*/ Wall right_wall;
            /*const*/ Wall top_wall;
            /*const*/ Wall bottom_wall;
            VisibleWall middle_wall;
            Sound goal_sound;
            Sound bounce_sound;
            unsigned int left_score;
            unsigned int rigth_score;

            Ball ball;
            std::unique_ptr<BasePaddle> left_paddle;
            std::unique_ptr<BasePaddle> right_paddle;

            std::vector<InputableComponent*> inputable_components;
            std::vector<UpdatableComponenet*> updatable_componenets;
            std::vector<DrawnableComponent*> drawnable_componenets;

            /**
             * handles the input phase
             * Reads from keyboard(maybe network later), mouse
            */
            void input_phase();

            /**
             * Updates the coordinates of moving objects(that extends Updatable)
            */
            void update_phase();

            /**
             * Drawn the drawnable objects
            */
            void draw_phase() const;

            /**
             * Handle the collission of paddles
            */
            void handle_paddle_collissions();
            
            /**
             * handle the collissions with ball
            */
            void handle_ball_collissions();

        public:
            Game(
                unsigned int height, 
                unsigned int width,
                unsigned int target_fps,
                const GameType game_type
            );
            void run();
      
            ~Game();

    };

};