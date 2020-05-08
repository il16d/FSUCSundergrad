
#ifndef STORE_H
#define STORE_H


#include "book.h"
#include <iostream>
using namespace std;


class store{

    //friend ostream &operator<<(ostream &out, const store &os);
    //friend ostream& operator<<(ostream& os, const Song& s);
  //  friend ostream& operator<<(ostream& os, const store& out);

public:
    store();
   ~store();
   // friend ostream &operator<<(ostream &out, const store &os);

    //friend ostream &operator<<(ostream &out, const store &os);
    void add(const char*title, const char *author, Genre e, int price);
    void find(const char*s);
    void sell(const char*s);
    void display();
    void summary(Genre f);
    void menu();
    void setmoney(double);
    double printmoney();
    void match(Genre g);

private:
    Book *arr;
    int capacity;
    int size;
    void grow();
    void decrease();
    double money;


};

#endif