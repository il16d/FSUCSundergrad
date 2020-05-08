#include "StudentList.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;



int main() {

    StudentList sl;
    string answer = "";
    string filename;
//	cout << sl.ImportFile("text1.txt") << endl;
//	cout << sl.ImportFile("text2.txt") << endl;
//	cout << sl.CreateReportFile("output.txt") << endl;
//	sl.ShowList();
    while(answer.compare("Q") != 0){
        cout << "*** Student List menu ***" << endl;
        cout << "I Import students from a file" << endl;
        cout << "S Show student list (brief)" << endl;
        cout << "E Export a grade report (to file)" << endl;
        cout << "M Show this Menu" << endl;
        cout << "Q Quit Program" << endl;
        getline(cin,answer);
        if(answer.compare("I") == 0){
            cout << "enter file name (with .txt): " << endl;
            getline(cin, filename);
            cout << sl.ImportFile(filename.c_str()) << endl;
        }
        else if ((answer.compare("S") == 0)){
            sl.ShowList();
        }
        else if ((answer.compare("E") == 0)){
            cout << "enter output file name: " << endl;
            cin >> filename;
            cout << sl.CreateReportFile(filename.c_str()) << endl;
        }
        else if ((answer.compare("M") == 0)){
            continue;
        }
    }
    cout << "Goodbye" << endl;
    return 0;
}
