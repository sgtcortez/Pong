#pragma once

#include <raylib.h>
#include <memory>
#include <vector>

#include "component/RenderComponent.hpp"
#include "component/InputComponent.hpp"
#include "component/UpdateComponent.hpp"

#include "object/Ball.hpp"
#include "object/Paddle.hpp"
#include "object/Pause.hpp"
#include "object/Score.hpp"
#include "object/Wall.hpp"
#include "object/VisibleWall.hpp"


namespace ramboindustries 
{
    namespace controller
    {

        enum class GameType 
        {
            CPU_VS_CPU,
            PLAYER_VS_CPU,
            PLAYER_VS_PLAYER,
            CPU_VS_PLAYER,
        };

        class Game
        {
            public:
                Game(
                    unsigned int height, 
                    unsigned int width,
                    unsigned int target_fps,
                    const GameType game_type
                );
                void run();
                ~Game();

            private:
                object::Wall left_wall;
                object::Wall right_wall;
                object::Wall top_wall;
                object::Wall bottom_wall;
                object::VisibleWall middle_wall;
                object::Pause pause;
                Sound goal_sound;
                Sound bounce_sound;

                object::Score left_score;
                object::Score right_score;

                object::Ball ball;
                std::unique_ptr<object::Paddle> left_paddle;
                std::unique_ptr<object::Paddle> right_paddle;

                std::vector<component::InputComponent*> input_components;
                std::vector<component::UpdateComponent*> update_componenets;
                std::vector<component::RenderComponent*> render_componenets;

                void input_phase();
                void update_phase();
                void render_phase() const;                

                void handle_paddle_collissions();
                void handle_ball_collissions();

        };
    };

};