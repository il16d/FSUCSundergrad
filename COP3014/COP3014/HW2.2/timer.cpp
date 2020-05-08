/* Name: Iho López Tobi
Date: February 5rd 2018
Section: 13
Assignment: Homework 2 (timer)
Due Date: February 7th 2018
About this project: This program takes the input of the user and returns a given distance for the given bird previously entered
 it also assumes that the users imput is going to be upper case.
Assumptions: the input of the users are only going to be characters and the correct numbers for the distance

All work below was performed by Iho López */

#include <iostream>
#include <iomanip>
using namespace std;
int main() {
// Here we start the menu for the user.
    cout << "African Swallow - A" << endl;
    cout << "African Swallow + Coconut - C" << endl;
    cout << "European Swallow - E" << endl;
    cout << "European Swallow + Coconut - S" << endl;
    cout << "Owl - O" << endl;
    cout << "Owl + Coconut - W" << endl;

// Prompting the user to enter a reference character for the bird.
    cout << "Enter the bird: " << endl;
    char animal;
    cin >> animal;

// Prompting the user to enter a distance.
    cout << "Enter the distance in Kilometers" << endl;
    double distance;
    cin >> distance;

/* to calculate the distance "distance = (m/s)", we multiply the users input by a thousand to convert it into meters
 and then we divide it by the speed of the bird.
 * We need to show 4 decimal places after the dot, so we use fixed and showpoint and then set the precision to four.
 * If the user inputs a letter not previously specified on the menu, then the program returns an error.
 * */
    switch (animal) {

        case 'A':
            cout<< showpoint;
            cout << fixed;
            cout<< setprecision(4);
            cout << (distance*1000)/15.8 << endl;
            break;

        case 'C':
            cout<< showpoint;
            cout << fixed;
            cout<< setprecision(4);
            cout << (distance*1000)/12.65 << endl;
            break;

        case 'E':
            cout<< showpoint;
            cout << fixed;
            cout<< setprecision(4);
            cout << (distance*1000)/15.2 << endl;
            break;

        case 'S':
            cout<< showpoint;
            cout << fixed;
            cout<< setprecision(4);
            cout << (distance*1000)/12 << endl;
            break;

        case 'O':
            cout<< showpoint;
            cout << fixed;
            cout<< setprecision(4);
            cout << (distance*1000)/13.88 << endl;
            break;

        case 'W':
            cout<< showpoint;
            cout << fixed;
            cout<< setprecision(4);
            cout << (distance*1000)/10.2 << endl;
            break;
        default: cout <<"Error: Invalid reference letter for the bird " << endl;

    }
    cout << endl;
    return 0;
}

