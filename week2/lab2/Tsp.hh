


#include <vector>
#include <algorithm>
#include <iostream>

#include "Point.hh"

using namespace std;


class TSPBaseSolver
{
    protected :
    
    vector<Point> m_points;
    vector<int> m_bestOrder;
    unsigned int m_pathLength;
    double m_shortestDistance;
    
    double computeCircuitLength( const vector<int> & order ) const;
    void loadPointFromConsole();

    public :

    void loadFromConsole();
    void findShortestPath();
    void showBestOrder() const;
    void showPoints() const;
};
