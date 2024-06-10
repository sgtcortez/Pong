#pragma once

#include "shape/Shape.hpp"
#include <vector>

namespace ramboindustries
{
    namespace controller
    {

        bool intersect(
            const shape::Shape& left, 
            const shape::Shape& right
        );

        bool insersect_one_of(
            const shape::Shape& left, 
            const shape::Shape& first_option, 
            const shape::Shape& second_option
        );
    };
};