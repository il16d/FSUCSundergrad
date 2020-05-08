#include<iostream>
#include <cstring>
#include <cctype>
#include "id.h"
using namespace std;



ID::ID()
{
    //char token ='#';
    age_=-1;
    SetName("#");
    Nlenght=-1;

}  //set name to # age to -1


ID::ID( char *nm, int ag)
{
    name_=nm;
    age_=ag;
    Nlenght= sizeof(nm);

} //regular constructor

ID::~ID()
{
    delete [] name_;


} //destructor

ID::ID( const ID& d)
{
    if(this!=&d)
    {
        age_=d.age_;
        delete[]name_;
        name_=new char[];

        for(int i=0; i<d.Nlenght; i++)
        {
            name_[i]=d.name_[i];
        }
    }
    //return *this;


} // copy constructor
void ID::SetName(const char* n )
{
    delete[]name_;
    name_= new char[strlen(n)];
    strcpy(name_,n);
}
void ID::SetAge(int ag)
{
    age_=ag;
}
const char* ID:: GetName()const
{
    char *temp;
    temp=name_;
    return temp;
}
int ID:: GetAge()const
{
    int ag=age_;
    return ag;
}

/*ID &ID::operator=(const ID &d) {
    return <#initializer#>;
}*/

ID &ID::operator=(const ID &d)
{
    if(this!=&d)
    {
        age_=d.age_;
        delete[]name_;
        name_=new char[];

        for(int i=0; i<d.Nlenght; i++)
        {
            name_[i]=d.name_[i];
        }
    }
    return *this;
}



ostream& ID:: operator<<(ostream &os, const ID &d)
{
    os<<d.name_<<'\t'<<d.age_<<endl;
    return os;

}