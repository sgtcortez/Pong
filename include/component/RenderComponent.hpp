#pragma once

namespace ramboindustries 
{
    namespace component
    {
        struct RenderComponent
        {
            virtual void render() const = 0;                  
        };
    }
};