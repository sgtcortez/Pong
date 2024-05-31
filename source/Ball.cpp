#include "pong/Ball.hpp"
#include "pong/Interface.hpp"

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <string>

using namespace ramboindustries;
using namespace std;

Ball::Ball(const float radius)
{
    // the ball speed can be increased as soon as the game runs
    this->speed.x = 250;
    this->speed.y = 250;
    this->radius = radius;
}

Ball::~Ball()
{}


void Ball::update(const float delta_time) 
{
    const Vector2 temp = Vector2Scale(speed, delta_time);
    center = Vector2Add(center, temp);
}

void Ball::draw()
{
    DrawCircle(center.x, center.y, radius, YELLOW);
}

ObjectType Ball::get_object_type() const
{
    return ObjectType::CIRCLE;
}

bool Ball::intersect(ShapeComponent* collider) 
{

    const auto type = collider->get_object_type();
    
    if (type == ObjectType::RECTANGLE)
    {
        RectangleShapeComponent* c = static_cast<RectangleShapeComponent*>(collider);
        return CheckCollisionCircleRec(
            this->center, 
            this->radius, 
            c->rectangle
        );
    } 

    else if (type == ObjectType::CIRCLE) 
    {
        // MUltiple balls maybe? 
    }

    return false;
}

void Ball::reverse_x()
{
    this->speed.x = this->speed.x * -1;
}

void Ball::reverse_y()
{
    this->speed.y = this->speed.y * -1;
}


void Ball::recenter()
{
    reverse_x();
    reverse_y();
    center.x = (float) GetScreenWidth() / 2;
    center.y = (float) GetScreenHeight() / 2;
}