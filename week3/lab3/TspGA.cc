

#include "TspGA.hh"

#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cassert>

using namespace std;




void TspGASolver::init( const char* filename,
                        int populationSize, int numGenerations,
                        double percentToKeep, double percentMutations  )
{
    m_populationSize = populationSize;
    m_numGenerations = numGenerations;
    m_percentToKeep = percentToKeep;
    m_percentMutations = percentMutations;
    
    loadFromFile( filename );
    showPoints();
    initializePopulation();
}

void TspGASolver::loadFromFile( const char* filename )
{
    ifstream _fileHandle ( filename );
    string _line;
    cout << "TspGASolver::loadFromFile> loading data from file " << filename << endl;
    if ( _fileHandle.is_open() )
    {
        // get first line
        getline( _fileHandle, _line );
        int _numPoints = atoi( _line.c_str() );
        m_pathLength = _numPoints;
        for ( int q = 0; q < _numPoints; q++ )
        {
            getline( _fileHandle, _line );
            parsePoint( _line );
        }

        _fileHandle.close();
    }

    cout << "TspGASolver::loadFromFile> finished loading" << endl;
}

void TspGASolver::parsePoint( const string &line )
{
    vector<double> _values;

    std::stringstream _ss;
    _ss.str( line );
    string _item;
    while ( getline( _ss, _item, ' ' ) )
    {
       _values.push_back( atof( _item.c_str() ) ); 
    }
    
    m_points.push_back( Point( _values[0], _values[1], _values[2] ) );
}


void TspGASolver::initializePopulation()
{
    cout << "TspGASolver::initializePopulation> Initializing population" << endl;
    
    for ( int q = 0; q < m_populationSize; q++ )
    {
        m_genomes.push_back( TspGenome( m_points.size() ) );
    }

    cout << "TspGASolver::initializePopulation> Finished initializing population" << endl;
}


bool TspGASolver::isShorterPath( const TspGenome &g1, const TspGenome &g2 ) 
{
    return g1.getCircuitLength() <= g2.getCircuitLength();
}

void TspGASolver::solve()
{
    int _populationToKeep = ( int ) ( m_percentToKeep * m_populationSize );
    int _populationToMutate = ( int ) ( m_percentMutations * m_populationSize );
    for ( int q = 0; q < m_numGenerations; q++ )
    {
        // Calculate fitness for each genomee 

        for ( unsigned int p = 0; p < m_genomes.size(); p++ )
        {
            double _circuitLength = computeCircuitLength( m_genomes[p].getOrder() ); 
            m_genomes[p].setCircuitLength( _circuitLength );
        }

        std::sort( m_genomes.begin(), m_genomes.end(), isShorterPath );

        /// for( unsigned int p = 0; p < m_genomes.size(); p++ )
        /// {
        ///     m_genomes[p].printToConsole();
        /// }
        /// break;
        // 
        
        if ( ( q + 1 ) % 10 == 0 )
        {
            cout << "Generation " << ( q + 1 ) << ": shortest path is:  " 
                 << m_genomes[0].getCircuitLength() << endl; 
        }

        // Keep the population needed and generate the remaining by crosslink
        for ( int p = _populationToKeep; p < m_populationSize; p++ )
        {
            int _indx1 = rand() % ( _populationToKeep );
            int _indx2 = 0;
            int _maxIter = 100;
            for ( int s = 0; s < _maxIter; s++ )
            {
                _indx2 = rand() % ( _populationToKeep );
                if ( _indx2 != _indx1 )
                {
                    break;
                }
            }
            
            m_genomes[p] = crossLink( m_genomes[_indx1], m_genomes[_indx2] );
        }

        // Mutate
        for ( int p = 0; p < _populationToMutate; p++ )
        {
            int _indx = 1 + rand() % ( _populationToMutate - 1 );
            m_genomes[_indx].mutate(); 
        }
    }
}

void TspGASolver::showResults()
{
    m_genomes[0].printToConsole();
}

TspGenome TspGASolver::crossLink( const TspGenome& g1, const TspGenome& g2 ) const
{
    int _size = m_points.size();
    int* _tmpContainer = new int[_size];
    for ( int q = 0; q < _size; q++ )
    {
        *( _tmpContainer + q ) = q;
    }
    
    vector<int> _crossedOrder;
    int _cutIndx = rand() % _size;
    /// cout << "_cutIndx: " << _cutIndx << endl;
    for ( int q = 0; q < _cutIndx; q++ )
    {
        _crossedOrder.push_back( ( g1.getOrder() )[q] );
        *( _tmpContainer + ( g1.getOrder() )[q] ) = -1;
    }
    
    // find which index is still available
    for ( int q = 0; q < _size; q++ )
    {
        int _nextIndx = -1;
        int _currIndx = ( g2.getOrder() )[q];

        for ( int p = 0; p < _size; p++ )
        {   
                
            if ( *( _tmpContainer + p ) == _currIndx )
            {
                _nextIndx = _currIndx;
                *( _tmpContainer + p ) = -1;
                break;
            }

        }
        
        if ( _nextIndx != -1 )
        {
            _crossedOrder.push_back( _nextIndx ); 
        }
    }
    
    assert( _crossedOrder.size() == ( unsigned int )_size );

    delete[] _tmpContainer;

    return TspGenome( _crossedOrder );
}

vector<TspGenome> TspGASolver::getGenomes() const
{
    return m_genomes;
}



TspGenome::TspGenome( int numPoints )
{
    m_circuitLength = 1e9;
    
    for ( int q = 0; q < numPoints; q++ )
    {
        m_order.push_back( q );
    }
    std::random_shuffle( m_order.begin(), m_order.end() );
}


TspGenome::TspGenome( const vector<int> &order )
{
    m_circuitLength = 1e9;
    m_order = order;
}

void TspGenome::mutate()
{
    int _maxIter = 20;
    unsigned int _indx1 = rand() % m_order.size();
    unsigned int _indx2 = 0;
    for ( int q = 0; q < _maxIter; q++ )
    {
        _indx2 = rand() % m_order.size();
        if ( _indx1 != _indx2 )
        {
            break;
        }
    }
    
    int _swap = m_order[_indx1];
    m_order[_indx1] = m_order[_indx2];
    m_order[_indx2] = _swap;
}


void TspGenome::printToConsole() const
{
    cout << "Genome : [ ";
    for ( unsigned int q = 0; q < m_order.size(); q++ )
    {
        cout << m_order[q] << " ";
    }
    cout << "]" << endl;
    cout << "fitness : " << m_circuitLength << endl;
}

double TspGenome::getCircuitLength() const
{
    return m_circuitLength;
}

vector<int> TspGenome::getOrder() const
{
    return m_order;
}

void TspGenome::setCircuitLength( double length )
{
    m_circuitLength = length;
}

void TspGenome::setOrder( const vector<int> &order )
{
    m_order = order;
}



