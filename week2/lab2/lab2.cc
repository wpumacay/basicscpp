

#include "Tsp.hh"








int main()
{
    TSPBaseSolver solver;

    solver.loadFromConsole();
    solver.showPoints();
    

    solver.findShortestPath();
    solver.showBestOrder();

    return 0;
}
