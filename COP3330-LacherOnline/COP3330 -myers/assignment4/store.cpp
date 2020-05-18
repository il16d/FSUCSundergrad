#include "store.h"
#include "book.h"
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;


store::store() {
    size=0;
    capacity=0;
    arr= new Book[capacity];


}

store::~store() {

    delete[] arr;
}

/*ostream &operator<<(ostream &out, const Book &os) {


        out<<os.title;
        out<<os.author;
        if (os.type == 0)
            out << "Fiction";
        else if (os.type == 1)
            out << "Mistery";
        else if (os.type == 2)
            out << "Sci-Fi";
        else if (os.type == 3)
            out << "Computer";

    out<<fixed;
    out<<setprecision(2);
    out<<os.price;





return out;

}*/

void store::setmoney(double m)
{
    money=m;

}

double store::printmoney()
{
    return money;
}


void store ::add(const char *title, const char *author, Genre e, int price) {

    if(size==capacity){

        grow();
    }
    Book add;
    add.Set(title,author,e,price);
    arr[size]=add;
    size++;
}

void store::find(const char *s) {

    for (int i=0; i<size; i++) {
        if (strcmp(arr[i].GetTitle(), s) == 0) {
            arr[i].Display();}

    }
    for (int i=0; i<size; i++){
        if(strcmp(arr[i].GetAuthor(),s)==0)
        {
            arr[i].Display();
        }
    }
}

void store::sell(const char *s) {

    int flag= -1;
    for(int i=0; i<size;i++){
        if(strcmp(arr[i].GetTitle(),s)==0)
        {
            flag=i;
        }
        if(flag!=-1)
        {
            for (int b=flag; b<size; b++)
            {
                arr[b-1]=arr[b];
                size--;
                if(size<capacity-4)
                {
                    decrease();
                }

            }
        } else if(flag== -1)
        {
            cout<<"No book found"<<endl;
        }
    }



}

void store::summary(Genre f)
{

    for(int i=0; i<size; i++)
    {
        if(arr[i].GetGenre()==f)
        {
            arr[i].Display();
        }
    }

}

void store::display()
{
    for (int i =0; i<size; i++){

        arr[i].Display();
    }
}


void store::grow()
{

    capacity=size+5;

    Book *temp= new Book[capacity];
    for(int i =0; i<size; i++)
    {
        temp[i]=arr[i];
    }
        delete [] arr;
        arr=temp;
    cout<<"Array resized to "<<capacity<<endl;


}
void store::decrease()
{
    capacity=size;
    Book *temp=new Book[capacity];
    for(int i=0; i<size; i++)
    {
        temp[i]=arr[i];

    }
    delete [] arr;
    arr=temp;
    cout<<"Array shrinking to: "<<capacity<<endl;


}
void store::match(Genre g)
{


        int num = 0;
        double p = 0.00;
        for(int i=0; i < size; i++)
        {
            if(g==arr[i].GetGenre())
            {
                arr[i].Display();
                p += arr[i].GetPrice();
                num++;
            }


}
}
void store::menu()
{

    cout<<"\n\n\t\t\t\t*** BOOKSTORE MENU ***\n";
    cout<<"\t\tA\t\tAdd a Book to Inventory\n";
    cout<<"\t\tF\t\tFind a book from Inventory\n";
    cout<<"\t\tS\t\tSell a book\n";
    cout<<"\t\tD\t\tDisplay the inventory list\n";
    cout<<"\t\tG\t\tGenre Summary\n";
    cout<<"\t\tM\t\tShow this Menu\n";
    cout<<"\t\tX\t\tExit Program\n";
}
