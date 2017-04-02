


#include <vector>
#include <algorithm>
#include <iostream>

#include "Point.hh"

using namespace std;


class TspBaseSolver
{
    private :

    void findShortestPath();

    protected :
    
    vector<Point> m_points;
    vector<int> m_bestOrder;
    unsigned int m_pathLength;
    double m_shortestDistance;
    
    double computeCircuitLength( const vector<int> & order ) const;
    void loadPointFromConsole();

    public :

    void loadFromConsole();

    virtual void init();
    virtual void solve();
    virtual void showResults();

    unsigned int getPathLength() const;

    void showBestOrder() const;
    void showPoints() const;
};
