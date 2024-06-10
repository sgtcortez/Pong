#include "shape/RectangleShape.hpp"
#include "shape/Shape.hpp"

using namespace ramboindustries;
using namespace shape;

Type RectangleShape::get_type() const 
{
    return Type::RECTANGLE;
}

const Rectangle RectangleShape::get_rectangle() const
{
    return rectangle;
}
