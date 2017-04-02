

#include "Tsp.hh"

using namespace std;



void TSPBaseSolver::loadFromConsole()
{
    cout << "Enter number of points: ";
    cin >> m_pathLength;
    cout << endl;
    
    for ( unsigned int q = 0; q < m_pathLength; q++ )
    {
       loadPointFromConsole();
    }    

}



void TSPBaseSolver::loadPointFromConsole()
{
    int x, y, z;
    cout << "Point: ";
    cin >> x >> y >> z;
    
    m_points.push_back( Point( x, y, z ) );
}


void TSPBaseSolver::showPoints() const
{
    for ( unsigned int q = 0; q < m_points.size(); q++ )
    {
        cout << "Point " << ( q ) << " : ";
        cout << m_points[q].getX() << " " <<
                m_points[q].getY() << " " <<
                m_points[q].getZ() << endl;
    }
}

void TSPBaseSolver::showBestOrder() const
{
    cout << "Best Order: [ ";
    for ( unsigned int q = 0; q < m_bestOrder.size(); q++ )
    {
        cout << m_bestOrder[q] << " ";
    }
    cout << " ]" << endl;

}

double TSPBaseSolver::computeCircuitLength( const vector<int> &order ) const
{
    double _result = 0.0;
    for ( unsigned int q = 0; q < order.size(); q++ )
    {
        _result += m_points[order[( q + 1 ) % order.size()]].distanceTo( m_points[order[q]] );
    }
    return _result;
}

void TSPBaseSolver::findShortestPath()
{
    m_shortestDistance = 1000000.0;
    vector<int> _order;
    for ( unsigned int q = 0; q < m_pathLength; q++ )
    {
        m_bestOrder.push_back( q );
        _order.push_back( q );
    }
    cout << "checking ..." << endl;
   
    while ( true )
    {
        double _distance = computeCircuitLength( _order );
        if ( _distance < m_shortestDistance )
        {
            m_bestOrder = _order;
            m_shortestDistance = _distance;
            cout << "best distance : " << _distance << endl;
        }

        if ( !next_permutation( _order.begin(), _order.end() ) )
        {
            break;
        }
    }
    cout << "finished" << endl;
}
