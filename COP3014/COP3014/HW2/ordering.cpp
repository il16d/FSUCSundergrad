/* Name: Iho López Tobi
Date: February 3rd 2018
Section: 13
Assignment: Homework 2 (ordering)
Due Date: February 7th 2018
About this project: This program orders the inputs of the users from biggest to smallest value
Assumptions: the input of the users are only going to be ints

All work below was performed by Iho López */


#include <iostream>
using namespace std;

int main() {

    //promting the user to input three values
    cout << "Enter three integers: " << endl;
    int x,y,z;
    cin >> x>>y>>z;


    if (x == y && x == z && y==z ) //this line makes sure that if all three numbers are the same then exit.
    {
        cout << "You entered the same number three times. Exiting " << endl;
        return 0;
    }

    else if (z<x && z<y && x<y) // This line is executed when y is bigger than x  but x is bigger than z (y>x>z)
    {
        cout << "The numbers in order are: " << y << "\t" << x << "\t"<< z << "\t"<< endl;

    }

    else if(x<=y && y<=z) //This line is executed when z is bigger than y but y is bigger than x or equal to x (z>y>x)
    {
        cout<< "The numbers in order are: " << z <<"\t"<< y <<"\t"<< x <<"\t"<< endl;

    }

    else if (y>x && y>z) //This line is executed when y is bigger than z but z is bigger than x (y>z>x)
    {
        cout<< "The numbers in order are: " <<y <<"\t"<< z <<"\t"<<x<<"\t" << endl;
    }

    else if (y<=x && x<z) //This line is executed when z is bigger than x but x is bigger than y or equal to y (z>x>y)
    {
        cout<< "The numbers in order are:  " << z<<"\t"<< x<<"\t"<< y <<"\t"<< endl;
    }

   else if (z<x && z<y ) //This line is executed when x is bigger than y but y is bigger than z (x>y>z)
    {
        cout << "The numbers in order are:  " << x << "\t" << y << "\t" << z << "\t" << endl;
    }

   else if (y<x && y<=z ) // This line is executed when x is bigger than z but z is bigger than y or equal to y (x>z>y)
    {
        cout << "The numbers in order are:  " <<x << "\t" << z << "\t" << y << "\t" << endl;

    }

    return 0;
}