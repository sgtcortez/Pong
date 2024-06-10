#pragma once

#include "component/InputComponent.hpp"
#include "Paddle.hpp"

namespace ramboindustries
{
    namespace object
    {
        class UserPaddle
        :
            public Paddle,
            public component::InputComponent
        {
            public:
                UserPaddle(
                    const PaddleSide side, 
                    const int width,
                    const int height
                );

                void input() override;
                void update(const float delta_time) override;

            private:
                const int keycode_up;
                const int keycode_down;

                int direction;
        };

    };
};