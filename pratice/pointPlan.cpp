# include <iostream>
# include "point1.h"
using namespace std;


int main()
{
    point p1(2.0, 3.0);
    p1.affiche();
    p1.deplace(1.0, -1.0);
    p1.affiche();
    return 0;
}

