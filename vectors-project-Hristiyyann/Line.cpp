#include "Line.h"
#include "Point.h"

Line::Line(const Point& p1, const Point& p2) 
{
    A = p1.y - p2.y;
    B = p2.x - p1.x;
    C = -(A * p1.x + B * p1.y);
}

Line Line::perpendicular(const Point& p) 
{
    return Line(-B, A, B * p.x - A * p.y);
}

double Line::get_A()
{
    return A;
}

double Line::get_B()
{
    return B;
}

double Line::get_C()
{
    return C;
}