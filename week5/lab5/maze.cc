
#include "maze.hh"

using namespace std;

Maze::Maze( int rows, int cols )
{
    m_numRows = rows;
    m_numCols = cols;

    m_cells = new MazeCell[( 2 * rows + 1 ) * ( 2 * cols + 1 )];
    // Initialize the maze to be empty
    clear();
}

Maze::Maze( const Maze &m )
{
    m_numRows = m.getNumRows();
    m_numCols = m.getNumCols();

    m_start = m.getStart();
    m_end = m.getEnd();

    int _arraySize = ( 2 * m_numRows + 1 ) * ( 2 * m_numCols + 1 );
    m_cells = new MazeCell[_arraySize];
    for ( int q = 0; q < _arraySize; q++ )
    {
        m_cells[q] = m.m_cells[q];
    }
}

Maze::~Maze()
{
    delete[] m_cells;
}

Maze & Maze::operator=( const Maze &m )
{
    if ( this != &m )
    {
        delete[] m_cells;
        m_numRows = m.getNumRows();
        m_numCols = m.getNumCols();
        m_start = m.getStart();
        m_end = m.getEnd();

        int _arraySize = ( 2 * m_numRows + 1 ) * ( 2 * m_numCols + 1 );
        m_cells = new MazeCell[_arraySize];
        for ( int q = 0; q < _arraySize; q++ )
        {
            m_cells[q] = m.m_cells[q];
        }
    }

    return *this;
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
    m_start = Location( row , col );
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
    for ( int p = 0; p < m_numRows; p++ )
    {
        for ( int q = 0; q < m_numCols; q++ )
        {
            clearWall( p, q, Direction::NORTH );
            clearWall( p, q, Direction::SOUTH );
            clearWall( p, q, Direction::WEST );
            clearWall( p, q, Direction::EAST );

            setCell( p, q, MazeCell::EMPTY );
        }
    }
}

void Maze::setAllWalls()
{
    for ( int p = 0; p < m_numRows; p++ )
    {
        for ( int q = 0; q < m_numCols; q++ )
        {
            setWall( p, q, Direction::NORTH );
            setWall( p, q, Direction::SOUTH );
            setWall( p, q, Direction::WEST );
            setWall( p, q, Direction::EAST );
        }
    }
}


int Maze::getArrayIndex( const Location &loc ) const
{
    return ( loc.row * ( 2 * m_numCols + 1 ) + loc.col );
}

Location Maze::getCellArrayCoord( int cellRow, int cellCol ) const
{
    assert( cellRow < m_numRows );
    assert( cellRow >= 0 );
    assert( cellCol < m_numCols );
    assert( cellCol >= 0 );
    return Location( 2 * cellRow + 1, 2 * cellCol + 1 );
}

Location Maze::getWallArrayCoord( int cellRow, int cellCol, Direction direction ) const
{
    Location _result = getCellArrayCoord( cellRow, cellCol );
    switch ( direction )
    {
        case Direction::NORTH : 
            _result.row -= 1;
            break;
        case Direction::SOUTH :
            _result.row += 1;
            break;
        case Direction::EAST :
            _result.col += 1;
            break;
        case Direction::WEST :
            _result.col -= 1;
            break;
        default :
            assert( true );
    }
    assert( _result.row >= 0 );
    assert( _result.row < 2 * m_numRows + 1 );
    assert( _result.col >= 0 );
    assert( _result.col < 2 * m_numCols + 1 );

    return _result;
}

MazeCell Maze::getCell( int cellRow, int cellCol ) const
{
    Location _loc = getCellArrayCoord( cellRow, cellCol );
    int _indx = getArrayIndex( _loc );
    assert( _indx >= 0 );
    assert( _indx < ( 2 * m_numRows + 1 ) * ( 2 * m_numCols + 1 ) );
    return m_cells[_indx];
}

void Maze::setCell( int cellRow, int cellCol, MazeCell val )
{
    Location _loc = getCellArrayCoord( cellRow, cellCol );
    int _indx = getArrayIndex( _loc );
    m_cells[_indx] = val;
}

Location Maze::getNeighborCell( int cellRow, int cellCol,
                                Direction direction ) const
{
    Location _loc( cellRow, cellCol );
    switch ( direction )
    {
        case Direction::NORTH :
            _loc.row -= 1;
            break;
        case Direction::SOUTH :
            _loc.row += 1;
            break;
        case Direction::WEST :
            _loc.col -= 1;
            break;
        case Direction::EAST :
            _loc.col += 1;
            break;
        default :
            assert( true );
    }
    assert( _loc.row >= 0 );
    assert( _loc.row < m_numRows );
    assert( _loc.col >= 0 );
    assert( _loc.col < m_numCols );
    
    return _loc;
}



bool Maze::hasWall( int cellRow, int cellCol, Direction direction ) const
{
    Location _loc = getWallArrayCoord( cellRow, cellCol, direction );
    int _indx = getArrayIndex( _loc );
    if ( m_cells[_indx] == MazeCell::WALL )
    {
        return true;
    }
    return false;
}

void Maze::setWall( int cellRow, int cellCol, Direction direction )
{
    Location _loc = getWallArrayCoord( cellRow, cellCol, direction );
    int _indx = getArrayIndex( _loc );
    m_cells[_indx] = MazeCell::WALL;
}

void Maze::clearWall( int cellRow, int cellCol, Direction direction )
{
    Location _loc = getWallArrayCoord( cellRow, cellCol, direction );
    int _indx = getArrayIndex( _loc );
    m_cells[_indx] = MazeCell::EMPTY;
}

bool Maze::isVisited( int cellRow, int cellCol ) const
{
    return getCell( cellRow, cellCol ) == MazeCell::VISITED;
}

void Maze::setVisited( int cellRow, int cellCol )
{
    setCell( cellRow, cellCol, MazeCell::VISITED );
}

void Maze::print( ostream &os ) const
{
    os << m_numRows << " " << m_numCols << endl;
    for ( int p = 0; p < m_numRows; p++ )
    {
        os << "+";
        for ( int q = 0; q < m_numCols; q++ )
        {
            if ( hasWall( p, q, Direction::NORTH ) )
            {
                os << "---";
            }
            else 
            {
                os << "   ";
            }
            os << "+";
        }
        os << endl;

        if ( hasWall( p, 0, Direction::WEST ) )
        {
            os << "|";
        }

        for ( int q = 0; q < m_numCols; q++ )
        {
            os << " ";
            if ( m_start.row == p && m_start.col == q )
            {
                os << "S";
            }
            else if ( m_end.row == p && m_end.col == q )
            {
                os << "E";
            }
            else
            {
                os << " ";
            }
            os << " ";

            if ( hasWall( p, q, Direction::EAST ) )
            {
                os << "|";
            }
            else
            {
                os << " ";
            }
        }
        os << endl;
    }
    
    os << "+";
    for ( int q = 0; q < m_numCols; q++ )
    {
        if ( hasWall( m_numRows - 1, q, Direction::SOUTH ) )
        {
            os << "---";
        }
        else
        {
            os << "   ";
        }
        os << "+";
    }
    os << endl;
}


bool Maze::isInRange( int row, int col ) const
{
    return ( row < m_numRows && row >= 0 ) &&
           ( col < m_numCols && col >= 0 );
}

bool Maze::isInRangeAfterAction( int row, int col, Direction direction ) const
{
    switch ( direction )
    {
        case Direction::SOUTH : row += 1; break;
        case Direction::NORTH : row -= 1; break;
        case Direction::WEST  : col -= 1; break;
        case Direction::EAST  : col += 1; break;
    }
    return isInRange( row, col );
}

Location Maze::getLocationAfterAction( int row, int col, Direction direction ) const
{
    Location _result( row, col );

    switch ( direction )
    {
        case Direction::SOUTH : _result.row += 1; break;
        case Direction::NORTH : _result.row -= 1; break;
        case Direction::WEST  : _result.col -= 1; break;
        case Direction::EAST  : _result.col += 1; break;
    }

    return _result;
}
