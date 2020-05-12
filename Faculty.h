/*
 * Faculty.h
 *
 * Faculty records are similar to student records, and will also require overloaded operators.
 * Faculty records contain an integer Faculty ID, a String name, a String level (lecturer,
 * assistant prof, associate prof, etc), a String department, and a list of integers
 * corresponding to all of the faculty member’s advisees’ ids. These are the only fields the
 * class contains.
 */

#ifndef FACULTY_H_
#define FACULTY_H_

#include <iostream>
#include <string>
#include "DoublyLinkedList.h"
#include "Person.h"
#include "Student.h"

using std::string;
using std::ostream;
class Faculty: public Person
{

        // Operator
        friend bool operator==(const Faculty &c1, const Faculty &c2);
        friend bool operator!=(const Faculty &c1, const Faculty &c2);
        friend bool operator>(const Faculty &c1, const Faculty &c2);
        friend bool operator<(const Faculty &c1, const Faculty &c2);
        friend bool operator==(const int &c2, const Faculty &c1);
        friend bool operator!=(const int &c2, const Faculty &c1);
        friend bool operator>(const int &c2, const Faculty &c1);
        friend bool operator<(const int &c2, const Faculty &c1);
        friend bool operator==(const Faculty &c1, const int &c2);
        friend bool operator!=(const Faculty &c1, const int &c2);
        friend bool operator>(const Faculty &c1, const int &c2);
        friend bool operator<(const Faculty &c1, const int &c2);
        friend ostream& operator <<(ostream& out, const Faculty& fac);

    public:

        Faculty(string name, int ID, string level) :
                Person(name, ID, level)
        {
        }

        Faculty(string name, int ID, string level, string department,
                DoublyLinkedList<int> studentIDList) :
                Person(name, ID, level), department(department), studentIDList(
                        studentIDList)
        {
        }

        Faculty(string name, int ID, string level, string department) :
                Person(name, ID, level), department(department)
        {
        }

        Faculty(Faculty const &source) :
                Person(source.getName(), source.getID(), source.getLevel())
        {
            department = source.department;

            DoublyLinkedList<int> *temp = new DoublyLinkedList<int>(
                    source.studentIDList);

            studentIDList = *temp;
        }

        virtual void printInfo()
        {
            cout << "Faculty Information\n----------\n";
            cout << "Faculty ID:" << getID() << "\n" << "Name: " << getName()
                    << "\n" << "Level: " << getLevel() << "\n"
                    << "Department: " << getDepartment() << "\n\n";
        }

        int getID() const
        {
            return Person::getID();
        }
        string getName() const
        {
            return Person::getName();
        }
        string getLevel() const
        {
            return Person::getLevel();
        }
        string getDepartment() const
        {
            return department;
        }

        bool ContainsStudent(int studIDnum) const
        {
            return (studentIDList.findData(studIDnum) >= 0);
        }

        bool AddStudent(int studIDNum)
        {
            if (!(ContainsStudent(studIDNum)))
            {
                studentIDList.insertFront(studIDNum);
                return true;
            }
            return false;
        }

        bool AddStudent(Student stud)
        {
            int studIDNum = stud.getID();
            if (!(ContainsStudent(studIDNum)))
            {
                studentIDList.insertFront(studIDNum);
                return true;
            }
            cout << "Student with that ID already exists\n";
            return false;
        }

        bool AddStudent(Student *stud)
        {
            int studIDNum = stud->getID();
            if (!(ContainsStudent(studIDNum)))
            {
                studentIDList.insertFront(studIDNum);
                return true;
            }
            cout << "Student with that ID already exists\n";
            return false;
        }

        bool RemoveStudent(int studIDNum)
        {
            if (studentIDList.removeIntKey(studIDNum) == -1)
            {
                cout << "Student not in list\n";
                return false;
            }
            return true;
        }

        bool RemoveStudent(Student stud)
        {
            int studIDNum = stud.getID();
            return RemoveStudent(studIDNum);
        }
        bool RemoveStudent(Student *stud)
        {
            int studIDNum = stud->getID();
            return RemoveStudent(studIDNum);
        }

        DoublyLinkedList<int> getStudentIDList() const
        {
            return studentIDList;
        }

        void AddIDToList(int studentIDNum)
        {
            studentIDList.insertFront(studentIDNum);
        }

        void printStudentListIDs()
        {
            studentIDList.printList();
        }

    private:
        string department;
        DoublyLinkedList<int> studentIDList;

};

bool operator==(const Faculty &c1, const Faculty &c2);
bool operator!=(const Faculty &c1, const Faculty &c2);
bool operator>(const Faculty &c1, const Faculty &c2);
bool operator<(const Faculty &c1, const Faculty &c2);
bool operator==(const int &c2, const Faculty &c1);
bool operator!=(const int &c2, const Faculty &c1);
bool operator>(const int &c2, const Faculty &c1);
bool operator<(const int &c2, const Faculty &c1);
bool operator==(const Faculty &c1, const int &c2);
bool operator!=(const Faculty &c1, const int &c2);
bool operator>(const Faculty &c1, const int &c2);
bool operator<(const Faculty &c1, const int &c2);
ostream& operator <<(ostream& out, const Faculty& fac);

#endif /* FACULTY_H_ */
