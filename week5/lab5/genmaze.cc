
#include "maze.hh"
#include <vector>
#include <cstdlib>

using namespace std;

namespace mazegen
{

    vector<Direction> calcDirections( const Maze &m, Location position )
    {
        vector<Direction> _dirs;
        Direction _choices[4] = { Direction::SOUTH, 
                                  Direction::NORTH,
                                  Direction::EAST,
                                  Direction::WEST };
        for ( int q = 0; q < 4; q++ )
        {
            Location _next = m.getLocationAfterAction( position.row, 
                                                       position.col,
                                                       _choices[q] );
            if ( !m.isInRange( _next.row, _next.col ) )
            {
                continue;
            }
            if ( m.isVisited( _next.row, _next.col ) )
            {
                continue;
            }
            _dirs.push_back( _choices[q] );
       }

        return _dirs;
    }

    void print_path( vector<Location> path )
    {
        for ( unsigned int q = 0; q < path.size(); q++ )
        {
            Location _loc = path[q];
            cout << " ( " << _loc.row << ", " << _loc.col << " ) ";
        }
        cout << endl;
    }

    Maze backtrack( int rows, int cols )
    {
        Maze m( rows, cols );
        
        vector<Location> _path;

        m.clear();
        m.setAllWalls();
        m.setStart( 0, 0 );
        m.setEnd( rows - 1, cols - 1 );
        
        _path.push_back( Location( 0, 0 ) );
        m.setVisited( 0, 0 );

        while ( !_path.empty() )
        {
            Location _loc = _path.back();
            m.setVisited( _loc.row, _loc.col );

            /// print_path( _path );

            if ( _loc == m.getEnd() )
            {
                _path.pop_back();
                continue;
            }

            // Get next posible directions
            vector<Direction> _posDirs = calcDirections( m, _loc );
            if ( _posDirs.empty() )
            {
                _path.pop_back();
                continue;
            }

            int _rindx = rand() % _posDirs.size();
            _path.push_back( m.getLocationAfterAction( _loc.row,
                                                       _loc.col,
                                                       _posDirs[_rindx] ) );
            m.clearWall( _loc.row, _loc.col, _posDirs[_rindx] );
        }
        
        return m;
    }






}






int main( int argc, char **argv )
{

    Maze _maze = mazegen::backtrack( 20, 10 );
    
    _maze.print( cout );

    return 0;
}
