

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int find_simple( const vector<int> &v, int value )
{
    for ( unsigned int q = 0; q < v.size(); q++ )
    {
        if ( v[q] == value )
        {
            return q;
        }
    }

    return -1;
}

void print_vector( const vector<int> &v )
{
    cout << "vector --- " << endl;
    
    for ( unsigned int q = 0; q < v.size(); q++ )
    {
        cout << v[q] << " ";
    }
    cout << endl;

    cout << "---------- " << endl;
}

int main()
{
    cout << "START **********************" << endl;

    vector<int> v;
    for ( int q = 0; q < 10; q++ )
    {
        int x;
        cin >> x;
        v.push_back( x );
    }

    for ( unsigned int q = 0; q < v.size(); q++ )
    {
        cout << v[q] << endl;
    }
    
    int _val;
    cout << "element to find: ";
    cin >> _val;

    int _indx = find_simple( v, _val );
    if ( _indx == -1 )
    {
        cout << "not found" << endl;
    }
    else 
    {
        cout << "found at index " << _indx << endl;
    }

    cout << "using stl find" << endl;

    vector<int>::iterator iter;
    iter = find( v.begin(), v.end(), _val );
    
    if ( iter != v.end() )
    {
        cout << "found value! " << *iter << endl;
    }
    else
    {
        cout << "couldnt find value :( " << endl;
    }
    
    cout << "sorting ...  " << endl;

    sort( v.begin(), v.end() );
    print_vector( v );

    cout << "END ************************" << endl;
    return 0;
}









