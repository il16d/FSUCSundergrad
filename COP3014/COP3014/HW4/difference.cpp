/* Assignment: Homework 4 ( special difference)
 * Due date: March 2nd 2018
 * About this project: This project is able to compute the special difference of a number and keep track of the sum of all the numbers and their differences.
 * Assumptions: This program assumes that 0 is entered to make the recording of numbers stop. If the difference of a number is negative, the program takes care of it by turning the number positive.
 * All work below was performed by Iho López.
 */



#include <iostream>
#include <cmath>

using namespace std;

int reverse( int num);
int difference (int x);




int main() {

  int x;
    cout << "Enter the numbers: " << endl;
    cin >> x;
    int sum = 0;


    while (x > 0) { //if x=0 then stop

        //We need to take the absolute value of the difference because the difference of a number reversed can return a negative number.
             sum = abs(difference(x))+sum; //Sum keeps track of all the differences of the numbers entered and adds them up.

            cin >> x;
        }


        cout << "The sum is " << sum << endl;

        return 0;
    }




//To reverse a number we ned to take the number and multiply it by ten and then add the remainder of the number when divided by 10.
    int reverse(int num) {
        int rev_num = 0;
        while (num > 0) {
            rev_num = rev_num * 10 + num % 10;
            num = num / 10;
        }
        return rev_num;
    }
//The difference is done by taking the number entered, reverse it and subtracting the number entered.
    int difference(int x) {

        x = (reverse(x) - x);


        return x;
    }

