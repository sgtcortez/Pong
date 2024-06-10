#include "object/UserPaddle.hpp"

using namespace ramboindustries;
using namespace component;
using namespace object;

/**
    * Since we let the user choose the left paddle and the right paddle.
    * we need to be able to choose the correct keycode
*/
UserPaddle::UserPaddle(const PaddleSide side, const int width, const int height)
:
    keycode_up(side == PaddleSide::LEFT ? KEY_W : KEY_UP),
    keycode_down(side == PaddleSide::LEFT ? KEY_S : KEY_DOWN)
{

    this->rectangle.height = height;
    this->rectangle.width = width;

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

void UserPaddle::input() 
{
    this->direction = 0;

    if (IsKeyDown(keycode_up))
    {
        this->direction++;
    }
    if (IsKeyDown(keycode_down))
    {
        this->direction--;
    }  
}

void UserPaddle::update(const float delta_time) 
{
    
    const float speed_y = 150;

    if (this->direction == 0)
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
    const auto value = this->direction * speed_y * delta_time;

    /*
     * For now, only the Y position can be updatable. 
     * However, we can easily implement left & right directions also
    */
    this->rectangle.y = this->rectangle.y - value;
}