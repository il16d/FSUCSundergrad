/* Assignment: Homework 4 ( palindrome primes)
 * Due date: March 2nd 2018
 * About this project: This project is able to look for the palindrome primes up to a given limit.
 * for this project we reused the same program we used to look for prime numbers adding the function used to reverse numbers and one more condition to look for palindrome primes.
 * Assumptions: No assumptions are made for this program. This program will terminate if a negative value or 0 is entered
 * All work below was performed by Iho López.
 */



#include<iostream>

using namespace std;


int reverse( int num);
int main() {


    int x = 1; // where we start.
    int i;      // i is the denominator
    int counter; //The counter keeps track of how many numbers have been entered in the program.
    int limit;  // up to what number the user wants the program to output the prime numbers.

    cout << "Please enter the upper limit: ";
    cin >> limit;

    if (limit<=1)
    {
        cout << "Number is negative. Goodbye. "<< endl;
    }
    else
        cout <<"The palindrome primes are: "<<endl;

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

        if (counter == 0 && x != 1){
            /*this makes sure that the counter starts at 0
            * and the number which what we start counting with is 1
            */

           if (reverse(x)==x){ //This applies the logic of if the number reversed is the same as teh number at that given time then cout.
               cout << x <<",";
           }
        }





    }

    return 0;
}

int reverse(int num) {
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}