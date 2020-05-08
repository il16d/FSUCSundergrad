#include "studentlist.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

StudentList::StudentList(){
    this->students = NULL;
    this->size = 0;
}

StudentList::~StudentList(){

    delete []this->students;
}

bool StudentList::ImportFile(const char* filename) {
    ifstream myfile;
    string fname;
    string lname;
    string course;
    double scores[8];
    char *flag; //flag
    int numberOfStudents;
    int i;
    myfile.open (filename);
    if (myfile.is_open()) {
        myfile >> numberOfStudents;
        // cout << "Printing number of students read: " << numberOfStudents << endl;
        //check if StudentList is empty or not
        if (this->size == 0) {
            this->students = new Student[numberOfStudents];
            i = 0;
            this->size = numberOfStudents;
        }
//		allocate more memory to list and copy
        else {
            Student *temp = new Student[size + numberOfStudents];
            copy(this->students, this->students + this->size, temp);
            i = size;
            this->size = numberOfStudents + size;
        }
        while(!myfile.eof()){
            for (int j = 0; j < numberOfStudents; j++) {
                getline(myfile, lname, ',');
                this->students[j].setLastName(lname);
                myfile.get();
                getline(myfile, fname);
                this->students[j].setFirstName(fname);
                // getline(myfile, course);
                myfile >> course;
                if (course == "Math") {
                    for (int k = 0; k < 8; k++) {
                        myfile >> scores[k];
                    }
                    this->students[j].setCourse(course, scores);
                }
                if (course == "History") {
                    for (int l = 0; l < 3; l++) {
                        myfile >> scores[l];
                    }
                    this->students[j].setCourse(course, scores);
                }
                if (course == "English") {
                    for (int e = 0; e < 4; e++) {
                        myfile >> scores[e];
                    }
                    this->students[j].setCourse(course, scores);
                    /*for (int k = 0; k < 8; k++) {
                        myfile >> scores[k];

                        this->students[k].setCourse(course, scores);
                    }*/

                }
            }
        }


        myfile.close();
        return true;
    }
    return false;
}




bool StudentList::CreateReportFile(const char* filename){
    //open file
    ofstream myfile;
    myfile.open (filename);

    //if success then create an report by subjects
    if (myfile.is_open()){  //(myfile.is_open()){
        myfile << "Student Grade Summary\n";
        myfile << "-----------------\n\n";
        myfile << "MATH CLASS" << endl;
        myfile << "Student Name\tFinal Exam\tFinal Avg\tLetter Grade\n";
        myfile << "-------------------------------------------------\n";
        for(int i = 0; i < this->size; i++){
            if(students[i].getCourseName()=="Math"){
                myfile << this->students[i].getFirstName() << " " << this->students[i].getLastName() << "\t";
                myfile << this->students[i].getFinalExam() << "\t";
                myfile << students[i].getGrade() << "\t";
                myfile << this->getLetterGrade(students[i].getGrade()) << endl;
            }

        }

        myfile << "\n\nHISTORY CLASS" << endl;
        myfile << "Student Name\tFinal Exam\tFinal Avg\tLetter Grade\n";
        myfile << "-------------------------------------------------\n";
        for(int i = 0; i < this->size; i++){
            if(students[i].getCourseName()=="History"){
                myfile << this->students[i].getFirstName() << " " << this->students[i].getLastName() << "\t";
                myfile << this->students[i].getFinalExam() << "\t";
                myfile << students[i].getGrade() << "\t";
                myfile << this->getLetterGrade(students[i].getGrade()) << endl;
            }

        }

        myfile << "\n\nENGLISH CLASS" << endl;
        myfile << "Student Name\tFinal Exam\tFinal Avg\tLetter Grade\n";
        myfile << "-------------------------------------------------\n";
        for(int i = 0; i < this->size; i++){
            if(students[i].getCourseName()=="English"){
                myfile << this->students[i].getFirstName() << " " << this->students[i].getLastName() << "\t";
                myfile << this->students[i].getFinalExam() << "\t";
                myfile << students[i].getGrade() << "\t";
                myfile << this->getLetterGrade(students[i].getGrade()) << endl;
            }

        }

        myfile << "\n\nOVERALL GRADE DISTRIBUTION\n\n";
        int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0;
        for(int i=0; i<this->size; i++){
            if(this->getLetterGrade(students[i].getGrade()) == "A"){
                cnt1++;
            }
            if(this->getLetterGrade(students[i].getGrade()) == "B"){
                cnt2++;
            }
            if(this->getLetterGrade(students[i].getGrade()) == "C"){
                cnt3++;
            }
            if(this->getLetterGrade(students[i].getGrade()) == "D"){
                cnt4++;
            }
            if(this->getLetterGrade(students[i].getGrade()) == "F"){
                cnt5++;
            }
        }
        myfile << "A:\t" << cnt1 << endl;
        myfile << "B:\t" << cnt2 << endl;
        myfile << "C:\t" << cnt3 << endl;
        myfile << "D:\t" << cnt4 << endl;
        myfile << "F:\t" << cnt5 << endl;

        myfile.close();
        return true;
    }
    return false;
}


void StudentList::ShowList() const{
    // print basic list data
    cout << "List of Students: " << endl;
    for(int i = 0; i < this->size; i++){
        cout << students[i].getFirstName() << " " << students[i].getLastName() << endl;
    }
}

string StudentList::getLetterGrade(double score){
    if(score >= 90){
        return "A";
    } else if (score < 90 && score >= 80){
        return "B";
    } else if (score < 80 && score >= 70 ){
        return "C";
    } else {
        return "F";
    }

}


Student::Student(){
    this->firstName = "";
    this->lastName = "";
    this->course = "";

}
Student::Student(string first, string last, string course, double scores[]){
    first=this->firstName;
    last= this->lastName;
    course= this->course;


    /* this->firstName = first;
     this->lastName = last;
     this->course = course;*/

    Student::setCourse(course,scores);

}

void Student::setFirstName(string name)  {

    // name = this->firstName;
    this->firstName = name;

}

void Student::setLastName(string name){

    // name=this->lastName;
    name = name.substr(1);
    this->lastName = name;

}
void Student::setCourse(string course, double scores[]){
    if(course=="Math"){

        double quizes[] = {scores[0], scores[1], scores[2], scores[3], scores[4]};
        this->math = MathStudent(quizes,scores[5], scores[6],scores[7]);


    }
    else if (course=="English"){
        this->english = EnglishStudent(scores[0],scores[1],scores[2],scores[3]);
    }
    else if (course=="History"){

        this->history = HistoryStudent(scores[0],scores[1],scores[2]);

    }
    this->course = course;
}

string Student::getFirstName(){
    return firstName;
}
string Student::getLastName() {
    return lastName;
}
string Student::getCourseName() {
    return course;
}
int Student::getFinalExam() {
    if(this->course=="Math"){
        return this->math.getFinalExam();
    } else if(this->course=="English"){
        return this->english.getFinalExam();
    } else if(this->course=="History"){
        return this->history.getFinalExam();
    }
    return 0;
}

double Student::getGrade() {
    if(this->course=="Math" ){
        return this->math.getFinalAverage();
    } else if(this->course=="English"){
        return this->english.getFinalAverage();
    } else if(this->course=="History"){
        return this->history.getFinalAverage();
    }
    return 0.0;
}





EnglishStudent::EnglishStudent(){
    this->courseName = "English";
    this->attendance = 0.0;
    this->midterm = 0.0;
    this->project = 0.0;
    this->finalExam = 0.0;
}


EnglishStudent::EnglishStudent(double attendance, double project, double midterm, double finalExam){
    this->courseName = "English";
    this->attendance = attendance;
    this->midterm = midterm;
    this->project = project;
    this->finalExam = finalExam;
}


double EnglishStudent::getFinalAverage(){
    return 0.1 * this->attendance + 0.3 * (this->midterm + this->project + this->finalExam);
}

string EnglishStudent::getCourseName(){
    return this->courseName;
}

int EnglishStudent::getFinalExam(){
    return this->finalExam;
}






HistoryStudent::HistoryStudent(){
    this->courseName = "History";
    this->termPaper = 0.0;
    this->midterm = 0.0;
    this->finalExam = 0.0;
}

HistoryStudent::HistoryStudent(double termPaper, double midterm, double finalExam){
    this->courseName = "History";
    this->termPaper = termPaper;
    this->midterm = midterm;
    this->finalExam = finalExam;
}

double HistoryStudent::HistoryStudent::getFinalAverage(){
    return 0.25 * this->termPaper + 0.35 * this->midterm + 0.4 * this->finalExam;
}

string HistoryStudent::HistoryStudent::getCourseName(){
    return this->courseName;
}

int HistoryStudent::getFinalExam(){
    return this->finalExam;
}







MathStudent::MathStudent(){
    this->courseName = "Math";
    this->test1 = 0.0;
    this->test2 = 0.0;
    this->finalExam = 0.0;
}

MathStudent::MathStudent(double quizzes[], double test1, double test2, double finalExam){
    this->courseName = "Math";
    for (int i = 0; i < 5; i++){
        this->quizes[i] = quizzes[i];
    }
    this->test1 = test1;
    this->test2 = test2;
    this->finalExam = finalExam;
}


double MathStudent::MathStudent::getFinalAverage(){
    double totalAvg = 0.0;
    for(int i = 0; i < 5; i++){
        totalAvg += this->quizes[i];
    }
    totalAvg = totalAvg / 5;
    return 0.15 * totalAvg + 0.25 * (this->test1 +this->test2) + 0.35 * this->finalExam;
}

string MathStudent::MathStudent::getCourseName(){
    return this->courseName;
}

int MathStudent::getFinalExam(){
    return this->finalExam;
}