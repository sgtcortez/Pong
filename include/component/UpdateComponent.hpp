#pragma once

namespace ramboindustries 
{
    namespace component
    {
        struct UpdateComponent
        {
            /**
            * We can not get the value directly from Raylib because we might have different delta
            * times when dealing with multiple updatable objects
            */
            virtual void update(const float delta_time) = 0;
        };
    };
};