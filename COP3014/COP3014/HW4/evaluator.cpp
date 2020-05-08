/* Assignment: Homework 4 ( evaluator)
 * Due date: March 2nd 2018
 * About this project: This project is able to compute taylor series expansion by taking two numbers from the user.
 * Assumptions: This program assumes that no negative numbers are going to be entered
 * All work below was performed by Iho López.
 */




#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


long long  factorial (long long  x);

double sum (double x, double n);


int main() {


int x,y;




  cout <<"Enter the value of x: "<< endl;
    cin>>x;
    cout<<"Enter the number of terms: "<<endl;
    cin>>y;

    //e series is number entered(x) power (y) /factorial(y)


    cout<<fixed;
    cout<<setprecision(3);
    cout<< "The val is: "<< sum(x,y);







return 0;
}

long long  factorial (long long  x)
{
    long i; // we need I and factorial to be longs because if not the function sum will cause to over shoot its capacity
    long fact=1;

    for (i=1; i<=x; i++)

        fact *=i;//for every i we multiply for avery value until we reach i.


    return fact;

}


 double sum (double x, double n) // we use doubles and long long just to prevent overshooting their capacities.
{
    double sum=0;
    for (long long i=0; i<=n-1; i++){// i starting at 0, and i being less or equal to one number less than n, we increment i.


        sum = sum+(pow(x, i) / factorial(i)); //the sum is going to add all the vaules of power x^i/i! until the limit


    }
    return sum;
}




