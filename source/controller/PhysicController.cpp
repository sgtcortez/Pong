#include "controller/PhysicController.hpp"

#include "shape/CircleShape.hpp"
#include "shape/RectangleShape.hpp"
#include "shape/Shape.hpp"
#include <raylib.h>

using namespace ramboindustries;
using namespace controller;
using namespace shape;

bool intersect_cr(
    const CircleShape& left, 
    const RectangleShape& right
);

bool intersect_rr(
    const RectangleShape& left, 
    const RectangleShape& right
);

bool ramboindustries::controller::intersect(
    const Shape &left, 
    const Shape &right
)
{
    if (left.get_type() == Type::CIRCLE && right.get_type() == Type::RECTANGLE) 
    {
        const CircleShape& leftCircle = static_cast<const CircleShape&>(left);
        const RectangleShape& rigthShape = static_cast<const RectangleShape&>(right);
        return intersect_cr(leftCircle, rigthShape);
    }
    else if (left.get_type() == Type::RECTANGLE && right.get_type() == shape::Type::CIRCLE)
    {
        const RectangleShape& leftRectangle = static_cast<const RectangleShape&>(left);
        const CircleShape& rightCircle = static_cast<const CircleShape&>(right);
        return intersect_cr(rightCircle, leftRectangle);            
    }
    else if (left.get_type() == Type::RECTANGLE && right.get_type() == Type::RECTANGLE) 
    {
        const RectangleShape& leftRectangle = static_cast<const RectangleShape&>(left);
        const RectangleShape& rigthShape = static_cast<const RectangleShape&>(right);

        return intersect_rr(leftRectangle, rigthShape);
    }

    // Not implemented yet
    return false;
}

bool ramboindustries::controller::insersect_one_of(
    const Shape &left, 
    const Shape &first_option, 
    const Shape &second_option
)
{
    if (ramboindustries::controller::intersect(left, first_option)) 
    {
        return true;
    }
    return ramboindustries::controller::intersect(left, second_option);
}



bool intersect_cr(const CircleShape& left, const RectangleShape& right) 
{
    return CheckCollisionCircleRec(
        left.get_center(), 
        left.get_radius(), 
        right.get_rectangle()
    );
}

bool intersect_rr(const RectangleShape& left, const RectangleShape& right)
{
    return CheckCollisionRecs(
        left.get_rectangle(), 
        right.get_rectangle()
    );
}