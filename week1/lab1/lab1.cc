
#include <iostream>

#include "Point.hh"

using namespace std;


double computeArea( Point &a, Point &b, Point &c )
{
    double sc = a.distanceTo( b );
    double sb = c.distanceTo( a );
    double sa = b.distanceTo( c );
    double sp = ( sc + sb + sa ) / 2;

    return sqrt( sp * ( sp - sa ) * ( sp - sb ) * ( sp - sc ) );
}


int main()
{

    Point points[3];
    for ( int q = 0; q < 3; q++ )
    {
        double x, y, z;
        cout << "Enter x y z : " << endl;
        cin >> x >> y >> z;
        points[q] = Point( x, y, z );
        cout << endl;
    }
    
    for ( int q = 0; q < 3; q++ )
    {
        cout << "Point " << ( q + 1 ) << " :  < " 
             << points[q].getX() << " "
             << points[q].getY() << " "
             << points[q].getZ() << " >" << endl;
    }
    
    cout << "Area is  : < " << computeArea( points[0], points[1], points[2] ) << " >" << endl;

    return 0;
}
