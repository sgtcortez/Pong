#include "shape/CircleShape.hpp"
#include "shape/Shape.hpp"
#include <raylib.h>

using namespace ramboindustries;
using namespace shape;

Type CircleShape::get_type() const
{
    return Type::CIRCLE;
}

const Vector2 CircleShape::get_center() const
{
    return center;
}

float CircleShape::get_radius() const
{
    return radius;
}