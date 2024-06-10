#pragma once

#include <raylib.h>

#include "component/RenderComponent.hpp"
#include "component/UpdateComponent.hpp"

#include "shape/CircleShape.hpp"


namespace ramboindustries
{
    namespace object
    {
        class Ball 
        :
            public component::RenderComponent,
            public component::UpdateComponent,
            public shape::CircleShape        
        {
            public:
                Ball(
                    const Vector2 center, 
                    const float radius
                );
                ~Ball() = default;

                void update(const float delta_time) override;
                void render() const override;

                void reverse_x();
                void reverse_y();
                void recenter();

            private:
                Vector2 speed;
        };
    };
};