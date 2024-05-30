#pragma once

#include "Interface.hpp"
#include <raylib.h>

namespace ramboindustries
{

    class Ball : public Updatable, public Drawnable, public CircleShape, Collider
    {
        private:
            Vector2 speed;
        public:

            Ball(const float radius);
            ~Ball();
            void update(const float delta_time) override;
            void draw() override;
            bool intersect(Shape* collider) override;
            ObjectType get_object_type() const override;

            void reverse_x();
            void reverse_y();
            void recenter();
    };

};