/*  * Assignment: Homework 6 ( stringops)
 * Due date: April 4rth 2018 (late turn in)
 * About this project: This project is able to print take in a sentence stored in a character array(C-strin) and look for
 * punctuation within the sentence, count the amount of vowels, count how many words were on the sentence and even find
 * the word you within the array.
 * Assumptions: This program assumes nothing.
 * All work below was performed by Iho López.
 */



#include <string>

#include <iostream>

using namespace std;


 int wordcounter(char string[] );
int vowelcounter(char string[] );
int puncCount(char string[]);
void findSubString(char string[]);

int main()
{

    char string[100];

    cout<< "Enter a text: "<<endl;
    cin.getline(string,100,'\n');


    cout << "Number of words: " << wordcounter(string) << endl;
    cout<<"Number of vowels: "<<vowelcounter(string)<<endl;
    cout<<"Number of punctuation: "<<puncCount(string)<<endl;

    findSubString(string);
    return 0;
}

int wordcounter(char string[])
{
    int words = 1;
    for(int i = 0; i < strlen(string);i++)  //For every amout characters that the sentence has, count the amouts of blank space
        if(string[i] == ' ')//for every space thats in the scentence increase the count of words.
            words++;
    return words;
}
int vowelcounter(char string[])
{
    int vowels = 0;
    for(int i = 0; i < strlen(string);i++)  //For every amout characters that the sentence has, count the amouts of blank space
        if(string[i] == 'a'|| string[i]=='e'|| string[i]=='i'|| string[i]=='o'|| string[i]=='u')//for every space thats in the scentence increase the count of words.
            vowels++;
    return vowels;
}
int puncCount(char string[]) {
    int counter = 0;
    for (int i = 0; i <strlen(string); i++) { //for every amount of characters that the sentences has count the blanck spaces.

        if (ispunct(string[i])) // use the function in sting library that looks for punctuation on the sentence "i" and keep adding them to the counter
        // int counter=0;
        counter++; //keeps track of how many punctuation sings are in the centence.
    }

return counter;
}

void findSubString(char string[]) {


    if (strstr(string,"you"))
        cout<<"you is a part of the string. "<<endl;
    else
        cout<<"you is not a part of the string. " <<endl;








    }






















