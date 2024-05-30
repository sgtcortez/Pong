#include "pong/Paddle.hpp"
#include "pong/Ball.hpp"

#include <cstdlib>
#include <raylib.h>

#include <iostream>
#include <string>

using namespace ramboindustries;
using namespace std;

/**
 * This function is to prevent the paddle to go outbounds
*/
void BasePaddle::limit() 
{
    const float y_position_top = this->rectangle.y;
    if (y_position_top < 0)
    {
        this->rectangle.y = 0;
    } 
    else 
    {
        this->rectangle.y = GetScreenHeight() - this->rectangle.height;
    }
}

void BasePaddle::draw()
{
    DrawRectangle(this->rectangle.x, this->rectangle.y, this->rectangle.width, this->rectangle.height, BLACK);
}


ObjectType BasePaddle::get_object_type() const
{
    return ObjectType::RECTANGLE;
}


bool BasePaddle::intersect(Shape* collider) 
{
    const auto type = collider->get_object_type();   
    if (type == ObjectType::RECTANGLE)
    {
        RectangleShape* c = static_cast<RectangleShape*>(collider);
        return CheckCollisionRecs(this->rectangle, c->rectangle);
    } 
    return false;
}


/**
    * Since we let the user choose the left paddle and the right paddle.
    * we need to be able to choose the correct keycode
*/
Paddle::Paddle(const bool left, const int width, const int height)
:
    keycode_up(left ? KEY_W : KEY_UP),
    keycode_down(left ? KEY_S : KEY_DOWN)
{

    this->rectangle.height = height;
    this->rectangle.width = width;

    /**
     * Paddle position must not be shared outside his class. 
     * since user can not plot it anywhere, its only updatable by keyboard events
    */

    if (left) 
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

void Paddle::input() 
{
    direction = 0;

    if (IsKeyDown(keycode_up))
    {
        direction++;
    }
    if (IsKeyDown(keycode_down))
    {
        direction--;
    }  
}

void Paddle::update(const float delta_time) 
{
    
    const float speed_y = 150;

    if (direction == 0)
    {
        /**
         * User pressed up and down at same time. 
         * So, there is no need to update paddle positions
        */
        return;
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

AIPaddle::AIPaddle(
    const Ball& ball,
    const bool left,
    const int width,
    const int height
)
:
    ball(ball),
    left(left)
{
    this->rectangle.height = height;
    this->rectangle.width = width;

    last_ball_position = ball.center;

    /**
     * Paddle position must not be shared outside his class. 
     * since user can not plot it anywhere, its only updatable by keyboard events
    */

    if (left) 
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
    if (left)
    {
        if (ball.center.x > screen_middle_x) 
        {
            // Ball is far
            return; 
        }
    } 
    else 
    {
        if (ball.center.x < screen_middle_x)
        { 
            // Ball is far
            return;
        }
    }

    // Ball is near the CPU PADDLE
    const float speed_y = 150;

    int direction = 0;

    bool center_paddle = false;

    if (left)
    {
        if (last_ball_position.x < ball.center.x)
        {
            center_paddle = true;
        }
    } 
    else 
    {
        if (last_ball_position.x > ball.center.x)
        {
            center_paddle = true;
        }
    }

    last_ball_position = ball.center;

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

        if (paddle_middle > ball.center.y)
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