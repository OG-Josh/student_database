/*
 * StudentAndFacultyTree.h
 *
 *  Created on: May 12, 2020
 *      Author: Johnny
 *      Email: johnnytuot@gmail.com
 */

#ifndef DATABASESYSTEM_H_
#define DATABASESYSTEM_H_

#include <fstream>
#include <iomanip>      // std::setprecision
#include <iostream>

#include <stdio.h>
#include <sstream>
#include <string>

#include "BST.h"

#include "FileHandler.h"
#include "Faculty.h"
#include "Student.h"
#include "UndoStates.h"


using namespace std;

const string STUDENT_TABLE_NAME = "studentdatabase.bin";
const string FACULTY_TABLE_NAME = "facultydatabase.bin";

class DatabaseSystem {
public:

    enum EnumStates {
        None, ChangedState
    };

    DatabaseSystem() {
    }

    /**
     * Load database from file
     */
    void readStudentDatabaseFromFile();

    /**
     * Read faculty from file
     */
    void readFacultyDatabaseFromFile();

    /**
     * System running
     */
    void running();

private:
    void PrintAllStudents() const;
    void PrintAllFalculty() const;
    void FindAndDisplayStudent(int id) const;
    void FindAndDisplayFaculty(int id) const;
    void FindAndDisplayStudentsAdvisor(int id) const;
    void FindAndDisplayAdvisorsStudents(int id) const;
    void AddStudent();
    void DeleteStudent(int IDNum);
    void AddFacultyMember();
    void DeleteFacultyMember(int IDnum);
    void ChangeStudentAdvisor(int StudentID, int FacultyID);
    void RemoveStudentFromFacultyRef(int StudentID, int FacultyID);
    void RollBack();
    void Exit();
    bool studentInFacultyList(int studID, int facID);
    UndoStates currUndo;
    BST<Student> student_database;
    BST<Faculty> faculty_database;
    FileHandler file_utility;
};

#endif /* DATABASESYSTEM_H_ */
