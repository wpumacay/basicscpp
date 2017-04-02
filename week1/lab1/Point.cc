

#include "Point.hh"



Point::Point()
{
    m_x_coord = 0;
    m_y_coord = 0;
    m_z_coord = 0;
}

Point::Point( double x, double y, double z )
{
    m_x_coord = x;
    m_y_coord = y;
    m_z_coord = z;
}

Point::~Point()
{
    // no-op
}

double Point::distanceTo( Point& other )
{
    return sqrt( ( m_x_coord - other.getX() ) * ( m_x_coord - other.getX() ) +
                 ( m_y_coord - other.getY() ) * ( m_y_coord - other.getY() ) + 
                 ( m_z_coord - other.getZ() ) * ( m_z_coord - other.getZ() ) );
}


// Mutators

void Point::setX( double x )
{
    m_x_coord = x;
}

void Point::setY( double y )
{
    m_y_coord = y;
}

void Point::setZ( double z )
{
    m_z_coord = z;
}

// Accessors

double Point::getX()
{
    return m_x_coord;
}

double Point::getY()
{
    return m_y_coord;
}

double Point::getZ()
{
    return m_z_coord;
}

