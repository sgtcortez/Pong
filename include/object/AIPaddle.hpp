#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"


namespace ramboindustries
{
    namespace object
    {
        class AIPaddle 
        :
            public Paddle
        {
            public:
                AIPaddle(
                    const Ball& ball,
                    const PaddleSide side,
                    const int width, 
                    const int heigth
                );
                void update(const float delta_time) override;
            private:
                const Ball& ball;
                const PaddleSide side;
                Vector2 ball_last_position;
        };

    };
};