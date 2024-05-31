#pragma once

#include <raylib.h>

namespace ramboindustries 
{

    struct InputableComponent
    {
        virtual void input() = 0;
    };

    struct  UpdatableComponenet
    {
        /**
         * We can not get the value directly from Raylib because we might have different delta
         * times when dealing with multiple updatable objects
        */
        virtual void update(const float delta_time) = 0;
    };

    struct DrawnableComponent
    {
        virtual void draw() = 0;                  
    };

    enum class ObjectType 
    {
        CIRCLE,
        RECTANGLE
    };

    struct ShapeComponent 
    {
        virtual ObjectType get_object_type() const = 0;
    };

    struct RectangleShapeComponent : public ShapeComponent
    {
        public:
            Rectangle rectangle;        
    };

    struct CircleShapeComponent : public ShapeComponent 
    {
        public:
            Vector2 center;
            float radius;
    };

    struct ColliderComponent
    {   
        virtual bool intersect(ShapeComponent* collider) = 0;  
    };

};