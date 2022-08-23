#include <iostream>
#include "geom.hpp"
using namespace std;

int main () {
    char input;
    Point p1,p2;
    Line l1,l2;
    cin>> input;
    switch(input) {
    case 'c': // construct
        cin >> input;
        switch(input) {
        case 'l': // line from two points
            cin >> p1 >> p2;
            cout << Line(p1, p2) << endl;
            break;
        case 'c': // collinear line from line and a point
            cin >> l1;
            cin >> p1;
            cout << l1.parallel(p1) << endl;
            break;
        case 'o': // orthogonal/perpendicular line from a line and a point
            cin >> l1;
            cin >> p1;
            cout << l1.perpendicular(p1) << endl;
            break;
        }
        break;
    case 'v': // verify
        cin >> input;
        switch(input) {
        case 'c': // if two lines are parallel
            cin >> l1;
            cin >> l2;
            cout << boolalpha << l1.parallel(l2) << endl;
            break;
        case 'p': // if two lines are perpendicular
            cin >> l1;
            cin >> l2;
            cout << boolalpha << l1.perpendicular(l2) << endl;
            break;
        }
        break;
    }

    return 0;
}
