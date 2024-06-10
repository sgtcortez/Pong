#pragma once

#include "Wall.hpp"
#include "component/RenderComponent.hpp"

namespace ramboindustries
{
    namespace object
    {
        class VisibleWall 
        :
            public Wall,
            public component::RenderComponent
        {
            public:
                VisibleWall(const Rectangle rectangle);
                void render() const override;
        };
    };
};