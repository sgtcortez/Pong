#pragma once

#include "Interface.hpp"
#include "pong/Ball.hpp"
#include <raylib.h>

namespace ramboindustries
{

    struct BasePaddle : public RectangleShape, public Drawnable, public Collider, public Updatable
    {
        virtual ~BasePaddle() = default;
        void limit();
        void draw() override;
        bool intersect(Shape* collider) override;
        ObjectType get_object_type() const override;
    };


    class Paddle : public BasePaddle, public Inputable
    {

        private:
            const int keycode_up;
            const int keycode_down;

            /**
             * The paddle can go up & down only
            */
            int direction;

        public:        
            /**
             * Is the user controlling the left or the right paddle?
            */
            Paddle(const bool left, const int width, const int height);

            void input() override;
            void update(const float delta_time) override;
    };


    class AIPaddle : public BasePaddle
    {

        private:
            const Ball& ball;
            const bool left;
            Vector2 last_ball_position;
        public:
            AIPaddle(
                // For this AI, we need to know where the ball is
                const Ball& ball,
                const bool left, 
                const int width, 
                const int height
            );

            void update(const float delta_time) override;
    };

};