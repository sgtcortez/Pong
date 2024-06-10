#pragma once

#include "shape/RectangleShape.hpp"

#include <raylib.h>

namespace ramboindustries
{
    namespace object
    {
        class Wall
        :
            public shape::RectangleShape
        {
            public:
                Wall(const Rectangle rectangle);
        };
    };
};