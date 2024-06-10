#pragma once

#include <raylib.h>

#include "Shape.hpp"

namespace ramboindustries
{
    namespace shape
    {
        struct RectangleShape : public Shape
        {
            public:
                Type get_type() const override;
                const Rectangle get_rectangle() const;
            protected:
                Rectangle rectangle;        
        };
    }
};