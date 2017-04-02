

#include "TspGA.hh"



int main()
{
    TspGASolver solver;

    solver.init( "test-500.txt", 
                 1000, 300, 
                 0.2, 1.0  );
        
    solver.solve();

    solver.showResults();

    return 0;
}
