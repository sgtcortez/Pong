#include "object/AIPaddle.hpp"

using namespace ramboindustries;
using namespace component;
using namespace object;

AIPaddle::AIPaddle(
    const Ball& ball,
    const PaddleSide side,
    const int width,
    const int height
)
:
    ball(ball),
    side(side)
{
    this->rectangle.height = height;
    this->rectangle.width = width;

    ball_last_position = ball.get_center();

    /**
     * Paddle position must not be shared outside his class. 
     * since user can not plot it anywhere, its only updatable by keyboard events
    */

    if (side == PaddleSide::LEFT) 
    {
        /**
         * If its left, we start 0 + 10 for X and in the middle for Y
        */
        this->rectangle.x = 10;
        this->rectangle.y =  (float) GetScreenHeight() / 2 - (float) height / 2;
    } 
    else 
    {
        this->rectangle.x = GetScreenWidth() - width - 10;
        this->rectangle.y =  (float) GetScreenHeight() / 2 - (float) height / 2;
    }

}

void AIPaddle::update(const float delta_time)
{

    const int screen_middle_x = GetScreenWidth() / 2;

    /*
     * Improve this with math
     * Would be nice to discover the direction and where the ball is going
    */
    if (side == PaddleSide::LEFT)
    {
        if (ball.get_center().x > screen_middle_x) 
        {
            // Ball is far
            return; 
        }
    } 
    else 
    {
        if (ball.get_center().x < screen_middle_x)
        { 
            // Ball is far
            return;
        }
    }

    // Ball is near the CPU PADDLE
    const float speed_y = 150;

    int direction = 0;

    bool center_paddle = false;

    if (side == PaddleSide::LEFT)
    {
        if (ball_last_position.x < ball.get_center().x)
        {
            center_paddle = true;
        }
    } 
    else 
    {
        if (ball_last_position.x > ball.get_center().x)
        {
            center_paddle = true;
        }
    }

    ball_last_position = ball.get_center();

    const int paddle_middle = this->rectangle.y + this->rectangle.height / 2;

    if (center_paddle) 
    {
        // The ball is going to the opposite mode
        // so we just center the ai paddle

        const int screen_middle = (int)GetScreenHeight() / 2; 

        if (screen_middle == paddle_middle)
        {
            direction = 0;
        }
        else if (this->rectangle.y > screen_middle) 
        {
            direction = 1;
        } 
        else 
        {
            direction = -1;
        }
    } 
    else 
    {

        if (paddle_middle > ball.get_center().y)
        {
            direction = 1;
        }
        else 
        {
            direction = -1;
        }
    }

    /**
     * We use delta time, to make our code runs the same for 30 FPS and 60 FPS
    */
    const auto value = direction * speed_y * delta_time;

    /*
     * For now, only the Y position can be updatable. 
     * However, we can easily implement left & right directions also
    */
    this->rectangle.y = this->rectangle.y - value;
}