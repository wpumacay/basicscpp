

#include <cmath>


class Point
{
    private :
    
    double m_x_coord;
    double m_y_coord;
    double m_z_coord;

    public :

    Point();
    Point( double x, double y, double z );

    ~Point();

    double distanceTo( const Point& other ) const;
    
    void setX( double x );
    void setY( double y );
    void setZ( double z );

    double getX() const;
    double getY() const;
    double getZ() const;
};


