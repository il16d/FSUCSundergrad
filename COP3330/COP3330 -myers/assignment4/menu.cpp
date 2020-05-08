#include <iostream>
#include <iomanip>
#include <cstring>
#include "book.h"
#include "store.h"

store s;

void Add()
{
    char g, x;
    Genre t;
    char title[31] = {'\0'};
    char author[21] = {'\0'};
    double p;
    cout <<"\nEnter title: ";
    cin.ignore(30, '\n');
    cin.getline(title, 30);
    cout <<"\nEnter author: ";
    cin.getline(author, 20);
    cout <<"\nEnter Genre - (F)iction, (M)ystery, (S)ci-Fi, or ";
    cout <<"(C)omputer: ";
    do
    {
        cin >> x;
        g = (toupper(x));
        if(g=='F')
        {
            t = FICTION;
            break;
        }
        if(g=='M')
        {
            t = MYSTERY;
            break;
        }
        if(g=='S')
        {
            t = SCIFI;
            break;
        }
        if(g=='C')
        {
            t = COMPUTER;
            break;
        }
        else
            cout << "Invalid genre entry, please re-enter\n";
    }
    while(g!='M' || g!='F' || g!='S' || g!='C');
    cout <<"Enter the price: ";
    do
    {
        cin >> p;
        if(p < 0)
            cout <<"Must enter a positive price. Please re-enter: ";
    }
    while(p < 0);
    s.add(title, author, t, p);
}

void Search()
{
    char search[31];
    cout<<"Enter search string (title or author): ";
    cin.ignore(30, '\n');
    cin.getline(search, 30);
    s.find(search);
}
void Sale()
{
    char search[31];
    cout <<"\nEnter Author to sell: ";
    cin.ignore(30, '\n');
    cin.getline(search, 30);
    s.sell(search);
}
void GenreSummary()
{
    char g, x;
    Genre t;
    cout <<"\nEnter Genre - (F)iction, (M)ystery, (S)ci-Fi, or ";
    cout <<"(C)omputer: ";
    do
    {
        cin >> x;
       toupper(x);
        if(x=='F')
        {
            t = FICTION;
            break;
        }
        if(x=='M')
        {
            t = MYSTERY;
            break;
        }
        if(x=='S')
        {
            t = SCIFI;
            break;
        }
        if(x=='C')
        {
            t = COMPUTER;
            break;
        }
        if(x=='c')
        {
            t = COMPUTER;
            break;
        }
        if(x=='s')
        {
            t = SCIFI;
            break;
        }
        if(x=='f')
        {
            t = FICTION;
            break;
        }
        if(x=='m')
        {
            t = MYSTERY;
            break;
        }
        else
            cout << "\nInvalid genre entry, please re-enter\n";
    }
    while(x!='M' || x!='F' || x!='S' || x!='C'|| x!='m' || x!='f' || x!='s' || x!='c');
    s.match(t);
}

int main()
{
    cout <<"*** Welcome to Bookstore Inventory Manager ***\n";
    cout <<"Please input the starting money in the cash register: ";
    double cash;
    cin >> cash;
    s.setmoney(cash);
    s.menu();
    char choice;
    do
    {
        cout<<"\n > ";
        cin>>choice;
        if(choice=='A' || choice=='a')
            Add();
        if(choice=='F' || choice=='f')
            Search();
        if(choice=='S' || choice=='s')
            Sale();
        if(choice=='D' || choice=='d')
            s.display();
        if(choice=='G' || choice=='g')
            GenreSummary();
        if(choice=='M' || choice=='m')
            s.menu();
        if(choice=='X' || choice=='x')
            break;
    }
    while(choice!='x' || choice!='X');
    cout <<"Cash in register: $ "<<fixed<<setprecision(2)<<s.printmoney();
    cout << "\nGoodbye!";
    return 0;
}

