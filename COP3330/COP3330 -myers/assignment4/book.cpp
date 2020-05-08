#include <iostream>
#include <cstring>
#include <iomanip>
#include "book.h"
using namespace std;

Book::Book()
// This constructor for class Entry initializes the name, phone number,
// and room number to be blank strings.
{
    strcpy(title, " ");
    strcpy(author, " ");
     type=type;
    price=0;

}
void Book::Set(const char* t, const char* a, Genre g, double p){
    strcpy(title, t);
    strcpy(author, a);
    price = p;
    if (price<0)
    {
        price=0;
    }
    type = g;
}
const char*Book::GetTitle() const {
    return title;
}

const char* Book::GetAuthor() const{
    return author;
}
double Book:: GetPrice() const{

    return price;

}
Genre Book:: GetGenre() const{

    return type;
}

void Book::Display() const{

    /* Display() function

The member function Display() should print out a Book object on one line
as follows, in an organized manner. (Monetary output should be in dollars
and cents notation, to two decimal places):
Title		              Author		  Genre		Price

Examples:
Programming for Dummies       Marvin Dipwart      Computer   $  24.95
Mutant Space Weasels          Bob Myers           Sci-Fi     $   5.95

*/
    char st;
    cout<<fixed;
    cout<<setprecision(2);
        st=type;
switch (st){


    case COMPUTER:  cout<<title<<"    "<<'\t'<<author<<"     "<<'\t'<<"Computer"<<"    "<<'\t'<<"$"<<'\t'<<price<<endl;
        break;
    case FICTION:  cout<<title<<"    "<<'\t'<<author<<"     "<<'\t'<<"Fiction"<<"    "<<'\t'<<"$"<<'\t'<<price<<endl;
        break;
    case MYSTERY:  cout<<title<<"    "<<'\t'<<author<<"     "<<'\t'<<"Mystery"<<"    "<<'\t'<<"$"<<'\t'<<price<<endl;
        break;
    case SCIFI:  cout<<title<<"    "<<'\t'<<author<<"     "<<'\t'<<"Sci-Fi"<<"    "<<'\t'<<"$"<<'\t'<<price<<endl;
}






}

/*int main(){

    Book d1;
    d1.Set("Basketball","run",SCIFI,10);
   /*cout<< d1.GetTitle()<<endl;
    cout<<d1.GetAuthor()<<endl;
    cout<<d1.GetGenre()<<endl;
    cout<<d1.GetPrice()<<endl;

    d1.Display();


    return 0;

}*/