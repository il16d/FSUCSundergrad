


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
    string line;
    char* token;
    int numberOfStudents;
    int i;
    myfile.open (filename);
    if (myfile.is_open())
    {

        getline(myfile, line);
        numberOfStudents = stoi(line);
        //check if StudentList is empty or not
        if(this->size == 0){
            this->students = new Student[numberOfStudents];
            i = 0;
            this->size = numberOfStudents;
        }
//		allocate more memory to list and copy
        else{
            Student *temp = new Student[size + numberOfStudents];
            copy(this->students, this->students+this->size, temp);
            i = size;
            this->size = numberOfStudents+ size;
        }

        while (!myfile.eof())
        {
            //convert to char[] and split string by commas
            char personal_info[line.size()];
            strcpy(personal_info, line.c_str());
            token = strtok(personal_info, "," );

            //stores first and last name
            this->students[i].setLastName(token);
            token = strtok (NULL, " ");
            this->students[i].setFirstName(token);

            //get the second line with the course name
            getline( myfile, line);

            char course_info[line.size()];
            strcpy(course_info, line.c_str());
            token = strtok(course_info, " " );

            string course = token;
            double scores[8];

            int j = 0;

            //reads all the second line with scores
            while (j < 8)
            {
                token = strtok (NULL, " ");
                if (token == NULL){
                    break;
                }
                sscanf(token,"%lf",&scores[j]);
                j++;
            }
            //set the scores and subject to the Student class
            this->students[i].setCourse(course, scores);
            i++;
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
    if (myfile.is_open()){
        myfile << "Math: " << endl;
        for(int i = 0; i < this->size; i++){
            if(students[i].getCourseName().compare("Math") == 0){

                myfile << this->students[i].getFirstName() << " " << this->students[i].getLastName() << ": ";
                myfile << "Final Exam: " << this->students[i].getFinalExam() << " ";
                myfile << "Final Grade: " << students[i].getGrade() << " ";
                myfile << "Letter Grade: " + this->getLetterGrade(students[i].getGrade()) << endl;
            }

        }

        myfile << "English: " << endl;
        for(int i = 0; i < this->size; i++){
            if(students[i].getCourseName().compare("English") == 0){

                myfile << this->students[i].getFirstName() << " " << this->students[i].getLastName() << ": ";
                myfile << "Final Exam: " << this->students[i].getFinalExam() << " ";
                myfile << "Final Grade: " << students[i].getGrade() << " ";
                myfile << "Letter Grade: " + this->getLetterGrade(students[i].getGrade()) << endl;
            }

        }

        myfile << "History: " << endl;
        for(int i = 0; i < this->size; i++){
            if(students[i].getCourseName().compare("History") == 0){

                myfile << this->students[i].getFirstName() << " " << this->students[i].getLastName() << ": ";
                myfile << "Final Exam: " << this->students[i].getFinalExam() << " ";
                myfile << "Final Grade: " << students[i].getGrade() << " ";
                myfile << "Letter Grade: " + this->getLetterGrade(students[i].getGrade()) << endl;
            }

        }

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
    this->firstName = first;
    this->lastName = last;
    this->course = course;
    Student::setCourse(course,scores);

}

void Student::setFirstName(string name)  {
    this->firstName = name;
}
void Student::setLastName(string name) {
    this->lastName = name;
}
void Student::setCourse(string course, double scores[]){
    if(course.compare("Math") == 0){

        double quizes[] = {scores[0], scores[1], scores[2], scores[3], scores[4]};
        this->math = MathStudent(quizes,scores[5], scores[6],scores[7]);


    }
    else if (course.compare("English") == 0){
        this->english = EnglishStudent(scores[0],scores[1],scores[2],scores[3]);
    }
    else if (course.compare("History") == 0){

        this->history = HistoryStudent(scores[0],scores[1],scores[2]);

    }
    this->course = course;

    //if coure == "Math" then do ....

}

string Student::getFirstName() const {
    return this->firstName;
}
string Student::getLastName() const {
    return this->lastName;
}
string Student::getCourseName() const {
    return this->course;
}
int Student::getFinalExam(){
    if(this->course.compare("Math") == 0){
        return this->math.getFinalExam();
    } else if(this->course.compare("English") == 0){
        return this->english.getFinalExam();
    } else if(this->course.compare("History") == 0){
        return this->history.getFinalExam();
    }
    return 0;
}

double Student::getGrade() const {
    if(this->course.compare("Math") == 0){
        return this->math.getFinalAverage();
    } else if(this->course.compare("English") == 0){
        return this->english.getFinalAverage();
    } else if(this->course.compare("History") == 0){
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


double EnglishStudent::getFinalAverage() const {
    return 0.1 * this->attendance + 0.3 * (this->midterm + this->project + this->finalExam);
}

string EnglishStudent::getCourseName() const{
    return this->courseName;
}

int EnglishStudent::getFinalExam() const{
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

double HistoryStudent::HistoryStudent::getFinalAverage() const{
    return 0.25 * this->termPaper + 0.35 * this->midterm + 0.4 * this->finalExam;
}

string HistoryStudent::HistoryStudent::getCourseName() const{
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


double MathStudent::MathStudent::getFinalAverage() const{
    double totalAvg = 0.0;
    for(int i = 0; i < 5; i++){
        totalAvg += this->quizes[i];
    }
    totalAvg = totalAvg / 5;
    return 0.15 * totalAvg + 0.25 * (this->test1 +this->test2) + 0.35 * this->finalExam;
}

string MathStudent::MathStudent::getCourseName() const{
    return this->courseName;
}

int MathStudent::getFinalExam() const{
    return this->finalExam;
}

/*
 * bool StudentList::ImportFile(const char* filename) {
  string line;
  ifstream myfile ("file.txt");
  if (myfile.is_open())
  {
  	string getline(myfile,line);
  	int current = 0;
  	int num = 1;
  	while(auto x: line)num = num*10+x-'0';
  	if(this->size == 0){

        this->students = new Student[num];
        this->size = numberOfStudents;
    }
//		allocate more memory to list and copy
    else{
        Student *temp = new Student[size + num];
        copy(this->students, this->students+this->size, temp);
        this->size = num+ size;

   }

    while ( getline (myfile,line) ){ //better if while not at the end of the file
      	string scores_and_subject;
      	getline(myfile,scores_and_subject);
      	string fname = "";
      	int i = 0;
      	while(i < line.length() and line[i] != ',')fname += line[i++];
      	string lname = s.substr(i+1);
      	this.students.setFirstName(fname);
      	this.students.setLastName(lname);
      	getline(myfile,line);
      	double scores[8];
      	int num_scores = 0;
      	line2 += " ";
      	bool flag = false;
      	int k = 0;
      	while(j < line.length()){
      		if(line[j] == ' '){
      			if(!flag){
      				flag = true;
      				course = temp;
      			}
      			else scores[k++] = 10*(line[0]-'0') + (line[1]-'0');
      			temp = "";
      		}
      		else temp += line[j];
      		j++;
      	}
      	this->students[current++].setCourse(course,scores);
    }
    myfile.close();
    return true;
  }

  else cout << "Unable to open file";
  return false;

 *
 *
 *
 *
 *
 *
 *
 * */