/*  * Assignment: Homework 3 ( primes)
 * Due date: Feb 19th 2018 (late turn in)
 * About this project: This project is able to print all the prime numbers up to a given limit .
 * Assumptions: This program assumes that only positive ints are going to be entered if not then the program exites.
 * All work below was performed by Iho López.
 */



#include <iostream>
using namespace std;
int main() {


    int x = 1; // where we start.
    int i;      // i is the denominator
    int counter; //The counter keeps track of how many numbers have been entered in the program.
    int limit;  // up to what number the user wants the program to output the prime numbers.

    cout << "Enter the upper limit: ";
    cin >> limit;

    if (limit<0)
    {
        cout << "Number is negative. Goodbye. "<< endl;
    }
    else
        cout <<"The prime numbers are: "<<endl;

    for (x; x <= limit; x++) {
        /* we start at one, if the number is smaller or equal to the limit (user input)
         * then the program increments the number to the next unit.
         */
        counter = 0;

        for (i = 2; i <= x/2; i++) {
            /* if i equals 2 then we output i
             *by dividing by two we skip every other even number and then we output i incremented by 2
             */

            if (x % i == 0) {
                /* This checks if the number is divisible by i then
                 * the program increments
                 */

                counter++;

            }
        }

        if (counter == 0 && x != 1)
            /*this makes sure that the counter starts at 0
            * and the number which what we start counting with is 1
            */
            cout << x <<",";



    }

    return 0;
}

