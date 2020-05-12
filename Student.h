/*
 * Student.h
 *
 * Student records will be stored in a Student class. Student records contain a unique
 * student ID (an integer), a String name field, a string level field (Freshman, Sophomore,
 * etc), a String major field, a double GPA field, and an integer advisor field, which will
 * contain the Faculty ID of their advisor. These are the only fields the class contains.
 *
 * The Student class must overload equality, less than, greater than operators, etc. so that we
 * can compare them to one another
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include <iostream>
#include <string>

#include "Person.h"

using std::string;
using std::ostream;
using std::cout;
using namespace std;
class Student: public Person
{
        // Operator
        friend bool operator==(const Student &c1, const Student &c2);
        friend bool operator!=(const Student &c1, const Student &c2);
        friend bool operator>(const Student &c1, const Student &c2);
        friend bool operator<(const Student &c1, const Student &c2);
        friend bool operator==(const int &c2, const Student &c1);
        friend bool operator!=(const int &c2, const Student &c1);
        friend bool operator>(const int &c2, const Student &c1);
        friend bool operator<(const int &c2, const Student &c1);
        friend bool operator==(const Student &c1, const int &c2);
        friend bool operator!=(const Student &c1, const int &c2);
        friend bool operator>(const Student &c1, const int &c2);
        friend bool operator<(const Student &c1, const int &c2);
        friend ostream& operator <<(ostream& out, const Student& stud);

    public:

        Student(string name, int ID, string level, string maj, int advisorID,
                double GPA) :
                Person(name, ID, level), student_major(maj), student_gpa(GPA), student_advisor(
                        advisorID)
        {
        }

        Student(Student const &source) :
                Person(source.getName(), source.getID(), source.getLevel())
        {
            this->student_major = source.student_major;
            this->student_gpa = source.student_gpa;
            this->student_advisor = source.student_advisor;
        }

        virtual void printInfo()
        {
            cout << "Student ID:" << getID() << "\n" << "Name: " << getName()
                    << "\n" << "Level: " << getLevel() << "\n" << "Major: "
                    << getMajor() << "\n" << "Advisor ID: " << getAdvisorID()
                    << "\n" << "GPA: " << getGPA() << "\n\n";
        }

        void setAdvisor(int inAdvisorID)
        {
            student_advisor = inAdvisorID;
        }

        string getMajor()
        {
            return student_major;
        }
        int getAdvisorID()
        {
            return student_advisor;
        }
        double getGPA()
        {
            return student_gpa;
        }

    private:
        string student_major;
        double student_gpa;
        int student_advisor;

};

bool operator==(const Student &c1, const Student &c2);
bool operator!=(const Student &c1, const Student &c2);
bool operator>(const Student &c1, const Student &c2);
bool operator<(const Student &c1, const Student &c2);

bool operator==(const int &c2, const Student &c1);
bool operator!=(const int &c2, const Student &c1);
bool operator>(const int &c2, const Student &c1);
bool operator<(const int &c2, const Student &c1);

bool operator==(const Student &c1, const int &c2);
bool operator!=(const Student &c1, const int &c2);
bool operator>(const Student &c1, const int &c2);
bool operator<(const Student &c1, const int &c2);

ostream& operator <<(ostream& out, const Student& Student);

#endif /* STUDENT_H_ */
