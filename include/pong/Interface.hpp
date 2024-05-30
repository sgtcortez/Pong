#pragma once

#include <raylib.h>

namespace ramboindustries 
{

    struct Inputable 
    {
        virtual void input() = 0;
    };

    struct  Updatable
    {
        /**
         * We can not get the value directly from Raylib because we might have different delta
         * times when dealing with multiple updatable objects
        */
        virtual void update(const float delta_time) = 0;
    };

    struct Drawnable 
    {
        virtual void draw() = 0;                  
    };

    enum class ObjectType 
    {
        CIRCLE,
        RECTANGLE
    };

    struct Shape 
    {
        virtual ObjectType get_object_type() const = 0;
    };

    struct RectangleShape : public Shape
    {
        public:
            Rectangle rectangle;        
    };

    struct CircleShape : public Shape 
    {
        public:
            Vector2 center;
            float radius;
    };

    struct Collider
    {   
        virtual bool intersect(Shape* collider) = 0;  
    };

};