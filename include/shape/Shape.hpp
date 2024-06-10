#pragma once

namespace ramboindustries
{
    namespace shape 
    {
        enum class Type 
        {
            CIRCLE,
            RECTANGLE
        };

        struct Shape 
        {
            virtual Type get_type() const = 0;
        };
    };
};