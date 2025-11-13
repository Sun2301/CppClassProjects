# include <iostream>
# include "point1.h"
using namespace std;


point::point(float a, float b) {
    x = a;
    y = b;
}

void point::affiche() {
    cout << "x: " << x << " y: " << y <<"\n" ;
}

void point::deplace(float dx, float dy) {
    x += dx;
    y += dy;
}