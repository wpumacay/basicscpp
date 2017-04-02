
#include "maze.hh"







Maze::Maze( int rows, int cols )
{
    m_numRows = rows;
    m_numCols = cols;

    m_cells = new MazeCell[( 2 * rows + 1 ) * ( 2 * cols + 1 )];
    // Initialize the cell

    for ( int p = 0; p < m_numRows; p++ )
    {
        for( int q = 0; q < m_numCols; q++ )
        {
            
        }
    }
}

Maze::Maze( const Maze &m )
{

}

Maze::~Maze()
{

}

Maze & operator=( const Maze &m )
{

}

int Maze::getNumRows() const
{
    return m_numRows;
}

int Maze::getNumCols() const
{
    return m_numCols;
}

Location Maze::getStart() const
{
    return m_start;
}

void Maze::setStart( int row, int col )
{
    m_start = Location( row, col );
}

Location Maze::getEnd() const
{
    return m_end;
}

void Maze::setEnd( int row, int col )
{
    m_end = Location( row, col );
}

void Maze::clear()
{

}

void Maze::setAllWalls()
{

}


int getArrayIndex( const Location &loc ) const
{
    int _extRow = 2 * loc.row + 1;
    int _extCol = 2 * loc.col + 1;


}


MazeCell Maze::getCell( int cellRow, int cellCol ) const
{

}

void Maze::setCell( int cellRow, int cellCol, MazeCell val )
{
    
}


