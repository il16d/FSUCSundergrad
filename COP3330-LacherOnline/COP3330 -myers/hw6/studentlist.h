#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class EnglishStudent{
public:
    EnglishStudent();
    EnglishStudent(double attendance, double project, double midterm, double finalExam);
    double getFinalAverage();
    string getCourseName();
    int getFinalExam();
private:
    string courseName;
    double attendance;
    double project;
    double midterm;
    double finalExam;
};




class HistoryStudent{
public:
    HistoryStudent();
    HistoryStudent(double termPaper, double midterm, double finalExam);
    double getFinalAverage();
    string getCourseName();
    int getFinalExam();
private:
    string courseName;
    double termPaper;
    double midterm;
    double finalExam;
};



class MathStudent{
public:
    MathStudent();
    MathStudent(double quizzes[], double test1, double test2, double finalExam);
    double getFinalAverage() ;
    string getCourseName();
    int getFinalExam();

private:
    string courseName;
    double quizes[5];
    double test1;
    double test2;
    double finalExam;
};

class Student{
public:
    Student();
    Student(string first, string last, string course, double scores[]);

    void setFirstName(string name);
    void setLastName(string name);
    void setCourse(string course, double scores[]);
    string getFirstName()  ;
    string getLastName()  ;
    string getCourseName() ;
    double getGrade() ;
    int getFinalExam() ;



private:
    string firstName;
   string lastName;
    string course;
    EnglishStudent english;
    HistoryStudent history;
    MathStudent math;

};

class StudentList
{
public:
   StudentList();		// starts out empty
   ~StudentList();		// cleanup (destructor)

   bool ImportFile(const char* filename);
   bool CreateReportFile(const char* filename);
   void ShowList() const;	// print basic list data
    string getLetterGrade(double score);


private:
    Student *students;
    int size;


};


