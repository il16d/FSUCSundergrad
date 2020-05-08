/*  * Assignment: Homework 3 ( letters)
 * Due date: Feb 19th 2018 (late turn in)
 * About this project: This project is able to print letters (J,E,C on the form of ASCR2 art)
 * Assumptions: This program assumes that no doubles are entered, other than thaht this program
 * makes sure that if the user enters a letter other than J,C or E the program keeps asking for a correct input.
 * Same happens with the size, if the size is not an even number greater or equal to 7 the program will not continue.
 * All work below was performed by Iho López.
 */


#include <iostream>
using namespace std;


int main() {
    int size;
    char ans;
    char letter;

    //we need to declare an overall do loop in order for the user to repeat the whole process again if this whishes to.

    do {
        cout << "Enter the size: ";
        cin >> size;
        while (size % 2 == 0 && size < 7) {
            cout << "Invalid size. Enter the size again ";
            cin >> size;
        }
        /* this while loop will make sure that if the user enters a size that is other than an odd number greater or equal to 7
         * the program will ask for an valid integer until this is entered.
         *
         */


        cout << "Enter the letter ";
        cin >> letter;
        while (letter != 'e' && letter != 'E' && letter != 'j' && letter != 'J' && letter != 'c' && letter != 'C') {
            cout << "Invalid letter. Enter the letter again ";
            cin >> letter;
        }
        /* this while loop will make sure that if the user enters a LETTER that is other than J,E or C
         * the program will ask for an valid letter until this is entered.
         *
         */


            switch (letter) {

                case 'e':
                case 'E':


                    for (int row = 0; row < size; row++) //this prints an L
                    {

                        if (row == 0) {
                            for (int col = 0; col < size; col++) {
                                cout << "*";
                            } //this prints the first line of stars for the letter E  (if the current row equals to 0 then this line prints)
                        } else if (row == (size - 1) / 2) {
                            for (int col = 0; col < size; col++)
                                cout << "*"; // this line prints the middle line of the E (since we can only enter non even ints, subtracting one from this and dividing it by 2 will take us to the middle of the E)
                        } else if (row == size - 1) {

                            for (int col = 0; col < size; col++) {
                                cout << "*"; // this prints the last line of the E (since we start at 0 one less than the size will take us to the last line)

                            }
                        } else cout << "*"; //this prints the left side of the E since its non of the previous conditions apply for this.
                        cout << endl;


                    }
                    break; // if user does not choose E then go to the next case.


                case 'c':
                case 'C':


                    for (int row = 0; row < size; row++)    // "row" tells us which row we are on right now, this prints the first line of stars for the letter C (if the current row equals to 0 then this line prints)
                    {
                        if (row == 0) {
                            for (int col = 0; col < size; col++) {
                                cout << "*";
                            }
                        } else if (row == size-1)     // if we are at the last row (since we start at 0 one less than the size will take us to the last line) then we will print the bottom of the C
                        {
                            for (int col = 0; col < size; col++) {
                                cout << "*";
                            }
                        } else cout << "*";    //this prints the left side of the C since its non of the previous conditions apply for this.
                        cout << endl;        //done with the row, go to the next line
                    }
                    break;


                case 'j':
                case 'J':


                    for (int row = 0; row < size; row++)    // "row" tells us which row we are on right now
                    {
                        if (row == 0) {
                            for (int col = 0; col < size; col++) {
                                cout << "*";
                            } // for this we need to print size number of stars.
                        } else if (row == size - 1)        // if we are at the last row
                        {
                            for (int col = 0; col < (size + 1) / 2; col++) {
                                cout << "*";
                            } //this statement puts us on the last line and only prints stars until half of size
                        } else if (row < (size - 1)) {
                            for (int col = 0; col < (size + 1) / 2; col++)
                                cout << " ";
                        } //this prints spaces of the left side of the letter

                        cout << "*"; //this prints stars on the middle of the letter J
                        cout << endl;        //done with the row, go to the next line
                    }
                    break;


            }
        cout << "Do you like to continue? (Y or N):  "; //this is the end of the loop do, here we as the user if this wishes to go again.
        cin >> ans; //the answer is recorded
        }

     while ((ans == 'Y' || ans == 'y')); // this while loop will make the user go all the way to the begining of the program. If the user does not whish to continue then the program returns 0.
    return 0;

}



