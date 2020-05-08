/*  * Assignment: Homework 6 ( palcheck)
 * Due date: April 4rth 2018
 * About this project: This project is able to print take in a sentence stored in a character array(C-strin) and look for
 * sentences that read the same forward and backwards
 * Assumptions: This program assumes nothing.
 * All work below was performed by Iho López.
 */



#include <iostream>
#include <string>
using namespace std;


string checkPalin(string sentence);


int main() {


    string arr;

    checkPalin(arr);

    cout<<arr;


    return 0;
}




string checkPalin(string sentence) {


    int N;

    int counter = 0;// keeps track of the how long the string is reverse counter ... circles through sentence from end to beginning
    bool decider = true;
    cout<<"Enter number of strings: "<<endl;
    cin>>N;

    // Enter the number of string asked by the user
    cout << "Enter "<<N<<" of strings: ";
    for(int i=0; i<=N; i++) { //for some reason if N is not increased by one the loop would cut the input short by one.
        getline(cin, sentence);
        //sentence++;
        }while(cin) {

//calculate the number of characters entered
        for (counter = 0; counter < sentence.length(); counter++);
        //for (counter=0; counter<sentence.size(); counter++);

        int middle = counter / 2;
        for (int i = 0; i <= middle; i++) //this loop goes up to the middle of the sentence or the word
        {
            counter--;
            if (isalpha(sentence[i]) && isalpha(sentence[counter])) {
                if (tolower(sentence[i]) == tolower(sentence[counter])) {
                    continue;
                }
                decider = false;

//We check the alphabetical order of the character in the sentence starting counting from the beginning and the sentence starting counting from the back
//Then we check is the whole sentence is in lower case

                /* else
                 {
                     cout <<sentence << "  is not a palindrome ";
                     decider = false;
                     break;
                 }*/
            } else {
                if (!(isalpha(
                        sentence[i]))) //If the sentence starting from the beginning is alphabetically the same we go one and check the second part of the sentence (counter++)
                    counter++;
                else if (!(isalpha(
                        sentence[counter]))) //here we start at the end of the sentence and if all the characters are alphabetically the same or repeated, we move ot the first part of the sentence
                    i--;


            }
        }}


        if (decider) //if the decider equals true then we have a palindrome and we cout it;
        {
            //counter++;
            // cout << counter;
            cout << sentence << " is a palindrome";
        } //this only prints if the last piece of text enetered is palindrome.
     cout<<sentence;


    return sentence;
    }





/* I can't seem to figure out how to print or check all the sentences that the user enetred instead
 * of only the last string entered.
 *
 * */













