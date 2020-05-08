#include <iostream>
using namespace std;


class ID{


//need assugnment operator overload


public:


    //need constructors  1. is default  2. 2argument constructor  3. need copy cons$  4. assignment operator
ID();  //set name to # age to -1
ID( char *nm, int ag); //regular constructor
~ID(); //destructor
ID( const ID&); // copy constructor
void SetName(const char* );
void SetAge(int);
const char* GetName()const;
int GetAge()const;
     ostream& operator<< (ostream& os , const ID& d);
ID& operator=(const ID& d);

private: 

char* name_;
int age_;

int Nlenght;

};

