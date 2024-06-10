#pragma once

#include "component/RenderComponent.hpp"
#include "component/UpdateComponent.hpp"
#include "shape/RectangleShape.hpp"

namespace ramboindustries
{
    namespace object
    {
        
        enum class PaddleSide
        {
            LEFT,
            RIGHT
        };
 
        class Paddle 
        : 
            public component::RenderComponent,
            public component::UpdateComponent,
            public shape::RectangleShape
        {
            public:
                virtual ~Paddle() = default;
                void limit();
                void render() const override;
        };
    };


};