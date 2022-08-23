#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
	
	Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
};

class Vector {
    double x, y;

public:
    Vector() : x(0), y(0) {}
    Vector(double x, double y) : x(x), y(y) {}
    // if we denote p1 and p2 as points A and B, their radius-vectors would be OA and OB
    Vector(Point p1, Point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

    // this function should return the sum of the current vector and another "other" as a new Vector
    Vector sum(const Vector& other) const {
        return Vector(x+other.x, y+other.y);
    }

    // this function should return the difference of the current vector and another "other" as a new Vector
    Vector difference(const Vector& other) const {
        return Vector(x-other.x, y-other.y);
    }

    // this function should return a boolean value, answering the question whether the current vector and another "other" are collinear
    bool is_colinear(const Vector& other) const {
        bool is_col = false;

        if(x/other.x ==  y/other.y)
        {
            is_col = true;
        } 
        return is_col;
    }

    // this function should return the length of the current vector
    double length() const {
        return sqrt(pow(x,2) + pow(y,2));
    }

    // this function should return the angle between the current vector and another "other"
    double angle(const Vector& other) const {
        double result = (x*other.x + y*other.y) / ((this->length())*(other.length()));
        return acos(result);
    }

    // this is for printing the vector
    friend ostream& operator<<(ostream& os, const Vector& c);
    // this is for entering the vector
    friend istream& operator>>(istream& in, Vector& v);
};


// this function should find the area of the triangle made up of the three points p1, p2, p3
double area(const Point& p1, const Point& p2, const Point& p3) {
    Vector v1(p1,p2);
    Vector v2(p2,p3);
    Vector v3(p3,p1);

    double length_p1 = v1.length();
    double length_p2 = v2.length();
    double length_p3 = v3.length();


    return (v1.length()*v2.length()*sin(v1.angle(v2))) / 2 ;
}
// this function should find the area of the figure made up of up to 50 points
double area(const Point points[50], int size) {
    return 0;
}

void vectors();
void triangleArea();
void area();

ostream& operator<<(ostream& os, const Vector& c);
istream& operator>>(istream& in, Vector& v);
istream& operator>>(istream& in, Point& p);

int main() {
    char input;
    cin >> input;

    switch (input) {
        case 'v':
            vectors();
            break;
        case 't': 
            triangleArea();
            break;
        case 's': 
            area();
            break;
        default:
            cout << "Invalid input" << endl;
    }

    return 0;
}

void vectors() {
    Vector v1, v2;
    cin >> v1 >> v2;
	
    cout << v1 << " + " << v2 << " = " << v1.sum(v2) << endl;
    cout << v1 << " - " << v2 << " = " << v1.difference(v2) << endl;
    cout << "Colinear: " << v1.is_colinear(v2) << endl;
    cout << "Length: " << v1.length() << endl;
    cout << "Angle: " << v1.angle(v2) * 180 / 3.1415926536 << "°" << endl;
}

void triangleArea() {
    Point p1, p2, p3;
    cin >> p1 >> p2 >> p3;
	
    cout << "Area triangle: " << area(p1, p2, p3) << endl;
}

void area() {
    int size;
    cin >> size;
	
    Point *points = new Point[size];
    for (int i = 0; i < size; i++) {
        cin >> points[i];
    }

    cout << "Area polygon: " << area(points, size) << endl;
    delete[] points;
}

// this is for printing the vector
ostream& operator<<(ostream& out, const Vector& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

// this is for inputing a vector
istream& operator>>(istream& in, Vector& v) {
    in >> v.x;
    in >> v.y;
	
    return in;
}

// this is for inputing a point
istream& operator>>(istream& in, Point& p) {
    in >> p.x;
    in >> p.y;
	
    return in;
}
