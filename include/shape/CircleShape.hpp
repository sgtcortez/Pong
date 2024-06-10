#pragma once

#include <raylib.h>

#include "Shape.hpp"

namespace ramboindustries
{
    namespace shape 
    {
        struct CircleShape : public Shape 
        {
            public:
                Type get_type() const override;
                const Vector2 get_center() const;
                float get_radius() const;
            protected:
                Vector2 center;
                float radius;
        };
    };
};