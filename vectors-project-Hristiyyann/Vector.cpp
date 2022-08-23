#include "Vector.h"
#include "Point.h"

Vector::Vector(Point start_point, Point end)
{
    x = start_point.x - end.x;
    y = start_point.y - end.y;
}

double Vector::get_x()
{
    return x;
}

double Vector::get_y()
{
    return y;
}

void Vector::Multiply(Vector& for_multiply, double size)
{
    for_multiply.x *= size;
    for_multiply.y *= size;
}