#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

class MyString{

    friend ostream& operator<<(ostream&, const MyString&);
    friend istream& operator>>(istream&, MyString&);
    friend istream& getline(istream&,  MyString& ,char delim);


    friend MyString operator+(const MyString& left, const MyString& right);

    friend bool operator<(const MyString&, const MyString&);
    friend bool operator>(const MyString&, const MyString&);
    friend bool operator<=(const MyString&, const MyString&);
    friend bool operator>=(const MyString&, const MyString&);
    friend bool operator==(const MyString&, const MyString&);
    friend bool operator!=(const MyString&, const MyString&);

public:

    MyString();
    MyString(const char*); //for c-strings
    MyString(int ); //integers to strings
    ~MyString();
    MyString( const MyString&);

    MyString& operator=(const MyString&);

    MyString& operator+=(const MyString&);

    char& operator[] (unsigned int ind);
    const char&operator[](unsigned int ind) const;

    MyString substring(unsigned int, unsigned int) const ; //subtract from first int up to second
    MyString substring(unsigned int)const ;
    MyString& insert(unsigned int index, const MyString& st); // insert at index x
    int indexOf(const MyString& st) const ;
    int getLength()const;
    const char* getCString()const;



private:
    int size;
    char *array;





};