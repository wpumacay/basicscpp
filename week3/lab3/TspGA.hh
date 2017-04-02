
#include "Tsp.hh"

class TspGenome;


class TspGASolver : public TspBaseSolver
{
    private :

    vector<TspGenome> m_genomes;

    int m_numGenerations;
    int m_populationSize;
    int m_percentMutations;
    double m_percentToKeep;
    
    void parsePoint( const string &line );
    void loadFromFile( const char* filename );
    
    void initializePopulation();
    
    public :
    
    using TspBaseSolver::init;
    void init( const char* filename,
               int populationSize, int numGenerations,
               double percentToKeep, double percentMutations  );

    void solve();
    void showResults();

    vector<TspGenome> getGenomes() const;


    TspGenome crossLink( const TspGenome& g1, const TspGenome& g2 ) const;
    static bool isShorterPath( const TspGenome &g1, const TspGenome &g2 );
};










class TspGenome
{
    private :
    
    double m_circuitLength;
    vector<int> m_order;

    public :
    
    TspGenome( int numPoints );
    TspGenome( const vector<int> &order );
    
    void mutate();
    void printToConsole() const;

    // Accessors
    
    double getCircuitLength() const;
    vector<int> getOrder() const;

    // Mutators

    void setCircuitLength( double length );
    void setOrder( const vector<int> &order );

};
