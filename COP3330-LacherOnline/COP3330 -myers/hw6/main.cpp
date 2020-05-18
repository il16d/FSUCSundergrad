#include <iostream>
#include "studentlist.h"

int main() {

    StudentList sl;
    string answer = "";
    char filename[21];
    //cout << sl.ImportFile("text1.txt") << endl;
//cout << sl.ImportFile("text2.txt") << endl;
    //  cout << sl.CreateReportFile("output.txt") << endl;
    sl.ShowList();
    while(answer!="Q"){
        cout << "*** Student List menu ***" << endl;
        cout << "I Import students from a file" << endl;
        cout << "S Show student list (brief)" << endl;
        cout << "E Export a grade report (to file)" << endl;
        cout << "M Show this Menu" << endl;
        cout << "Q Quit Program" << endl;
        getline(cin,answer);
        if(answer =="I"){
            cout << "enter file name (with .txt): " << endl;
            cin.getline(filename,21);
            cout << sl.ImportFile(filename) << endl;
        }
        else if ((answer=="S")){
            sl.ShowList();
        }
        else if ((answer=="E")){
            cout << "enter output file name: " << endl;
            cin >> filename;
            cout << sl.CreateReportFile(filename) << endl;
        }
        else if (answer=="M" ){
            continue;
        }
    }
    cout << "Goodbye" << endl;
    return 0;
}