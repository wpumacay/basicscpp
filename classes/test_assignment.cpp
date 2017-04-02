
#include <iostream>

using namespace std;

class Dog
{
    public :

    Dog()
    {
        this->age = 0;
        this->img = NULL;
    }

    ~Dog()
    {
        cout << "deleting..." << endl;
        destroy();
    }

    void destroy()
    {
        if ( img != NULL )
        {
            delete[] img;
            img = NULL;
        }  
    }

    void copy( Dog const &other )
    {
        this->age = other.age;
        this->img = new char[10];
        *( this->img ) = *( other.img );
        *( this->img + 1 ) = *( other.img + 1 );
    }

    void operator=( Dog const &other )
    {
        cout << "assinging..." << endl;
        if ( this == &other )
        {
            return;
        }
        destroy();
        copy( other );

    }

    Dog ( const Dog& other )
    {
        cout << "copy constructor" << endl;
        copy( other );
    }

    int age;
    char* img;
};


void use_dog( Dog& p_dog )
{      
    cout << "using dog" << endl;
    Dog _other;
    _other = p_dog;
    cout << "finished using dog" << endl;
}

void use_dog_2( Dog& p_dog )
{
    cout << "using dog again" << endl;
    
    Dog _other = p_dog;

    cout << "finished using dog again" << endl;
}

int main()
{
    Dog my_dog;
    my_dog.img = new char[10];
    *( my_dog.img ) = 'a';
    *( my_dog.img + 1 ) = 'b';
    
    cout << "dog_img: " << *( my_dog.img ) << " - " << *( my_dog.img + 1 ) << endl;

    use_dog( my_dog );
    use_dog_2( my_dog );

    cout << "dog_img: " << *( my_dog.img ) << " - " << *( my_dog.img + 1 ) << endl;
    cout << "end" << endl;
    return 0;
}



