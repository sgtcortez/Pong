#pragma once

#include "Interface.hpp"
#include <raylib.h>

namespace ramboindustries 
{

    class Wall :  public RectangleShapeComponent
    {
        public:
            Wall(Rectangle rectangle);
            ObjectType get_object_type() const override;
    };

    class VisibleWall : public Wall, public DrawnableComponent
    {
        public:    
            VisibleWall(Rectangle rectangle);
            void draw() override;
    };


};