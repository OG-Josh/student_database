/*
 * StudentAndFacultyTree.cpp
 *
 */

#include <iostream>
#include <limits>
#include <string>

#include "DatabaseSystem.h"
#include "DoublyLinkedList.h"
#include "Utility.h"

using std::cin;
using std::cout;

using std::getline;
using std::string;

void printMenu()
{
    cout
            << "1. Print all students and their information (sorted by ascending id #)"
            << endl;
    cout
            << "2. Print all faculty and their information (sorted by ascending id #)"
            << endl;
    cout << "3. Find and display student information given the students id"
            << endl;
    cout << "4. Find and display faculty information given the faculty id"
            << endl;
    cout
            << "5. Given a student’s id, print the name and info of their faculty advisor"
            << endl;
    cout
            << "6. Given a faculty id, print ALL the names and info of his/her advisees."
            << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id." << endl;
    cout
            << "11. Change a student’s advisor given the student id and the new faculty id."
            << endl;
    cout << "12. Remove an advisee from a faculty member given the ids"
            << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
}
int strToInt(string &str)
{
    int number;
    std::istringstream iss(str);
    iss >> number;
    return number;
}
double strToDouble(string &str)
{
    double number;
    std::istringstream iss(str);
    iss >> number;
    return number;
}

int getIDNumber()
{
    int result = -1;
    cout << "Enter a valid ID number (1 - " << INT_MAX - 1 << "): ";
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream linestream(line);
        if (!(linestream >> result))
        {
            cout << "Enter a valid ID number (1 - " << INT_MAX - 1 << "): ";
            continue;
        }
        if (result < 1 || result >= INT_MAX)
        {
            cout << "Enter a valid ID number (1 - " << INT_MAX - 1 << "): ";
            continue;
        }
        char errorTest;
        if (linestream >> errorTest)
        {
            cout << "Enter a valid ID number (1 - " << INT_MAX - 1 << "): ";
            continue;
        }
        break;
    }
    return result;
}

int getChoiceOption()
{
    int result = -1;
    cout << "Your option (1-14) > ";
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream linestream(line);
        if (!(linestream >> result))
        {
            cout << "Your option (1-14) > ";
            continue;
        }
        if (result < 1 || result > 14)
        {
            cout << "Your option (1-14) > ";
            continue;
        }
        char errorTest;
        if (linestream >> errorTest)
        {
            cout << "Your option (1-14) > ";
            continue;
        }
        break;
    }
    return result;
}

int getIDAbort()
{
    int result = -10;
    cout << "Enter a valid ID number (1 - " << INT_MAX - 1
            << "; -1 to exit): ";
    std::string line;
    cin.clear();
    while (std::getline(std::cin, line))
    {
        std::stringstream linestream(line);
        if (!(linestream >> result))
        {
            cout << "Enter a valid ID number (1 - " << INT_MAX - 1
                    << "; -1 to exit): ";
            continue;
        }
        if ((result != -1) && (result < 1 || result >= INT_MAX))
        {
            cout << "Enter a valid result number (1 - " << INT_MAX - 1
                    << "; -1 to exit): ";
            continue;
        }
        char errorTest;
        if (linestream >> errorTest)
        {
            cout << "Enter a valid result number (1 - " << INT_MAX - 1
                    << "; -1 to exit): ";
            continue;
        }
        break;
    }
    return result;
}
void getEnter()
{
    cout << "Press Enter to continue....";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void DatabaseSystem::running()
{
    cin.clear();
    int choice = 0;
    while (choice != 14)
    {
        printMenu();
        choice = getChoiceOption();
        cin.clear();
        if (choice >= 1 && choice <= 14)
        {
            switch (choice)
            {
            //1. Print all students and their information (sorted by ascending id #)
            case 1:
            {
                PrintAllStudents();
                break;
            }
                //2. Print all faculty and their information (sorted by ascending id #)
            case 2:
            {
                if (!faculty_database.isEmpty())
                    PrintAllFalculty();
                else
                {
                    cout << "No current Advisors" << endl;
                }
                break;
            }
                //3. Find and display student information given the students id
            case 3:
            {
                if (!faculty_database.isEmpty())
                {
                    if (!student_database.isEmpty())
                    {
                        int student_id;
                        student_id = getIDNumber();
                        FindAndDisplayStudent(student_id);
                    }
                    else
                    {
                        cout << "Student Tree is empty" << endl << endl;
                    }
                }
                if (faculty_database.isEmpty() && student_database.isEmpty())
                {
                    cout << "No current Advisors" << endl;
                }
                break;
            }
                //4. Find and display faculty information given the faculty id
            case 4:
            {
                if (!faculty_database.isEmpty())
                {
                    int faculty_id;
                    faculty_id = getIDNumber();
                    FindAndDisplayFaculty(faculty_id);
                }
                else
                {
                    cout << "No current Advisors" << endl;
                }
                break;
            }
                //5. Given a student’s id, print the name and info of their faculty advisor
            case 5:
            {
                if (!faculty_database.isEmpty())
                {
                    int faculty_id;
                    faculty_id = getIDNumber();
                    FindAndDisplayStudentsAdvisor(faculty_id);
                }
                else
                    cout << "No current Advisors" << endl;
                break;
            }
                //6. Given a faculty id, print ALL the names and info of his/her advisees.
            case 6:
            {
                if (!faculty_database.isEmpty())
                {

                    int faculty_id;
                    faculty_id = getIDNumber();
                    if (faculty_database.isContains(faculty_id))
                        FindAndDisplayAdvisorsStudents(faculty_id);
                    else
                        cout << "\nFaculty Member does not exist...\n";

                }
                else
                    cout << "No current Advisors" << endl;
                ;
                break;
            }
                //7. Add a new student
            case 7:
            {
                if (!faculty_database.isEmpty())
                {
                    currUndo.SaveState(student_database, faculty_database);
                    AddStudent();
                }
                else
                    cout << "No current Advisors" << endl;
                break;
            }
                //8. Delete a student given the id
            case 8:
            {
                if (!faculty_database.isEmpty())
                {
                    int student_id;
                    char yesNo = '~';
                    while (yesNo != 'Y' && yesNo != 'y' && yesNo != 'N'
                            && yesNo != 'n')
                    {
                        cout << "Continue?... (Y/N): ";
                        cin >> yesNo;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (yesNo == 'Y' || yesNo == 'y')
                        {
                            cout << "Student ID: ";
                            student_id = getIDNumber();
                            int count = 0;
                            char cont = '~';
                            while (!student_database.isContains(student_id))
                            {
                                cout << "Student ID: " << student_id
                                        << " does not exist...\n";

                                while (cont != 'Y' && cont != 'y'
                                        && cont != 'N' && cont != 'n')
                                {

                                    cout << "Continue?... (Y/N): ";
                                    ;

                                    cin >> cont;
                                    cin.clear();
                                    cin.ignore(
                                            numeric_limits<streamsize>::max(),
                                            '\n');
                                }
                                if (cont == 'n' || cont == 'N')
                                {
                                    cout << "Aborting Operation...\n";
                                    break;
                                }
                                cont = '~';

                                student_id = getIDNumber();
                                cin.clear();
                                count++;
                            }
                            // SAVE - STUDENT EXISTS - DELETE
                            currUndo.SaveState(student_database,
                                               faculty_database);
                            DeleteStudent(student_id);
                        }
                    }
                }
                else
                {
                    cout << "No current Advisors" << endl;
                    ;
                }
                break;
            }
                //9. Add a new faculty member
            case 9:
            {
                // SAVE
                currUndo.SaveState(student_database, faculty_database);
                AddFacultyMember();
                break;
            }
                //10. Delete a faculty member given the id.
            case 10:
            {
                if (!faculty_database.isEmpty())
                {
                    if (!faculty_database.hasOneObject())
                    {
                        int IDnum = -10;
                        cout << "Advisor ID - " << "TO DELETE - ";
                        while (!faculty_database.isContains(IDnum))
                        {
                            if (IDnum == -1)
                                break;
                            IDnum = getIDAbort();
                        }
                        if (IDnum != -1)
                        {
                            currUndo.SaveState(student_database,
                                               faculty_database);
                            DeleteFacultyMember(IDnum);
                        }
                        else
                            cout << "Aborting...\n";
                    }
                    else
                    {
                        cout << "Only one advisor remains...\n"
                                << "Cannot delete...\n";
                    }

                }
                else
                {
                    cout << "No current Advisors" << endl;
                    ;
                }
                break;
            }
                //11. Change a student’s advisor given the student id
                //    and the new faculty id.
            case 11:
            {
                if (!faculty_database.isEmpty()
                        && !faculty_database.hasOneObject())
                {
                    if (!student_database.isEmpty())
                    {
                        int studentID = 0, advisorID = 0;
                        cout << "Advisor ID - ";
                        advisorID = getIDNumber();
                        while (!faculty_database.isContains(advisorID))
                        {
                            cout << "Advisor" << " does not exist...\n";
                            cout << "Advisor ID - ";
                            advisorID = getIDNumber();
                        }
                        cout << "Student ID -";
                        studentID = getIDNumber();
                        while (!student_database.isContains(studentID))
                        {
                            cout << "Student" << " does not exist...\n";
                            cout << "Student ID -";
                            studentID = getIDNumber();
                        }
                        if (!student_database.isContains(studentID))
                        {
                            cout << "Student" << " does not exist...\n"
                                    << "Operation aborted\n";
                            break;
                        }
                        currUndo.SaveState(student_database, faculty_database);
                        ChangeStudentAdvisor(studentID, advisorID);
                    }
                    else
                        cout << "No current Students" << endl;
                    ;
                }
                else if (faculty_database.hasOneObject())
                    cout << "Only one advisor... can not reassign...\n";
                else
                {
                    cout << "No current Advisors" << endl;
                    ;
                }
                break;
            }
                //12. Remove an advisee from a faculty member given the ids
            case 12:
            {
                if (!faculty_database.isEmpty())
                {
                    if (!student_database.isEmpty())
                    {
                        cout << "\nStudents without advisors must"
                                << " be manually changed during"
                                << " runtime or at program start...\n";

                        char yesNo = '~';
                        while (yesNo != 'Y' && yesNo != 'y' && yesNo != 'N'
                                && yesNo != 'n')
                        {
                            cout << "Continue?... (Y/N): ";
                            cin >> yesNo;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),
                                       '\n');
                            if (yesNo == 'Y' || yesNo == 'y')
                            {
                                int studentID = 0, advisorID = 0;
                                cout << "Advisor ID - ";
                                advisorID = getIDNumber();
                                while (!faculty_database.isContains(advisorID))
                                {
                                    cout << "Advisor"
                                            << " does not exist...\n";
                                    cout << "Advisor ID - ";
                                    advisorID = getIDNumber();
                                }
                                cout << "Student ID -";
                                studentID = getIDNumber();
                                while (!student_database.isContains(studentID))
                                {
                                    cout << "Student"
                                            << " does not exist...\n";
                                    cout << "Student ID -";
                                    advisorID = getIDNumber();
                                }
                                // Will SAVE within function if found
                                RemoveStudentFromFacultyRef(studentID,
                                                            advisorID);
                            }
                        }
                    }
                    else
                        cout << "No current Students" << endl;
                    ;
                }
                else
                    cout << "No current Advisors" << endl;
                ;
                break;
            }
                //13. Rollback
            case 13:
            {
                RollBack();
                break;
            }
                //14. Exit
            case 14:
            {
                Exit();
                break;
            }
            default:
                break;
            }
            if (choice != 14)
            {
                cin.clear();
                getEnter();
            }
        }
        else
        {
            cout << "incorrect entry\n";
        }
    }
}

void DatabaseSystem::readFacultyDatabaseFromFile()
{

    try
    {
        ifstream inputFile;
        if (file_utility.open(inputFile, FACULTY_TABLE_NAME))
        {
            if (!file_utility.isEmptyFile(inputFile))
            {
                string faculty_name, faculty_department, faculty_level;
                int faculty_ID = 0;
                int line_counter = 0;
                string line;
                while (getline(inputFile, line))
                {
                    // ID
                    if (line_counter == 0)
                    {
                        line.erase(0, 4);
                        faculty_ID = strToInt(line);
                    }
                    // Name
                    if (line_counter == 1)
                    {
                        line.erase(0, 6);
                        faculty_name = line;
                    }
                    // Level
                    if (line_counter == 2)
                    {
                        line.erase(0, 12);
                        faculty_level = line;
                    }
                    // department
                    if (line_counter == 3)
                    {
                        line.erase(0, 12);
                        faculty_department = line;
                    }
                    if (line_counter == 4)
                    {
                        /*
                         |1111 2222 3333 4444 5555|
                         */
                        line = line.substr(1, line.size() - 2);
                        DoublyLinkedList<int> *student_list =
                                new DoublyLinkedList<int>();
                        stringstream stream(line);
                        int n;
                        while (stream >> n)
                        {
                            student_list->insertFront(n);
                        }
                        Faculty* new_faculty = new Faculty(faculty_name,
                                                           faculty_ID,
                                                           faculty_level,
                                                           faculty_department,
                                                           *student_list);
                        faculty_database.insert(*new_faculty);
                        delete new_faculty;
                        delete student_list;
                    }
                    line_counter++;
                    if (line_counter > 4)
                    {
                        line_counter = 0;
                    }
                }
                if (inputFile.bad())
                {
                    throw Error(
                            "The error when read database file. Please check");
                }
                else if (!inputFile.eof())
                {
                    throw Error("Look like some issue with file format");
                }
                else if (line_counter != 0)
                {
                    throw Error("Interrupted data file. Please check!");
                }
            }
        }
        if (inputFile.is_open())
        {
            inputFile.close();
        }
        else
        {
            cout << "DEBUG: Try to create faculty database file: "
                    << FACULTY_TABLE_NAME << endl;
            std::ofstream output(FACULTY_TABLE_NAME, std::ios::out);
            if (!output.is_open())
            {
                cout
                        << "CAN NOT open file for write. Please check your system!";
            }
            else if (output.is_open())
            {
                output.close();
            }
        }
    }
    catch (Error &e)
    {
        cout << e.what() << "\n";
        throw e;
    }

}

void DatabaseSystem::readStudentDatabaseFromFile()
{
    try
    {
        ifstream inputFile;
        if (file_utility.open(inputFile, STUDENT_TABLE_NAME))
        {
            if (!file_utility.isEmptyFile(inputFile))
            {
                string student_name, student_major, student_level;
                int student_id = 0, advisor_ID = 0;
                double student_gpa = 0;
                int field_counter(0);
                string line;
                while (getline(inputFile, line))
                {
                    // First field is student ID
                    if (field_counter == 0)
                    {
                        student_id = strToInt(line);
                        while (student_id < 1)
                        {
                            cout << "Stored ID is invalid.\n";
                            cout << "Student ID - ";
                            student_id = getIDNumber();
                        }
                    }
                    // Next line if student name
                    if (field_counter == 1)
                    {
                        student_name = line;
                    }
                    // Next line is level of this student
                    if (field_counter == 2)
                    {
                        student_level = line;
                    }
                    // Read major
                    if (field_counter == 3)
                    {
                        student_major = line;
                    }
                    // Read GPA
                    if (field_counter == 4)
                    {
                        student_gpa = strToDouble(line);
                    }
                    // Read advisor
                    if (field_counter == 5)
                    {
                        advisor_ID = strToInt(line);
                        while (advisor_ID < 1
                                || !faculty_database.isContains(advisor_ID))
                        {
                            cout
                                    << "Look like file store invalid infomation. Some mismatch with faculty database. Current faculty: \n";
                            faculty_database.printTree();
                            cout << "Advisor ID - ";
                            advisor_ID = getIDNumber();
                        }
                        // Check the faculty have mentor this student or not. Need to update both
                        if (faculty_database.isContains(advisor_ID))
                        {
                            if (faculty_database.get(advisor_ID).ContainsStudent(
                                    student_id)
                                    && !student_database.isContains(student_id)
                                    && !(faculty_database.get(advisor_ID).getStudentIDList().findDuplicateData(
                                            student_id) > 0))
                            {
                                Faculty* currentFaculty = new Faculty(
                                        faculty_database.get(advisor_ID));
                                // Add this student to faculty database
                                currentFaculty->AddStudent(student_id);
                                // Remove this advisor. Then add it to update data
                                faculty_database.deleteValue(advisor_ID);
                                faculty_database.insert(*currentFaculty);
                            }
                            // Have faculty and don't need to update
                            else if (!faculty_database.get(advisor_ID).ContainsStudent(
                                    student_id)
                                    && !student_database.isContains(student_id)
                                    && !(faculty_database.get(advisor_ID).getStudentIDList().findDuplicateData(
                                            student_id) > 0))
                            {
                                if (!faculty_database.get(advisor_ID).ContainsStudent(
                                        student_id))
                                {
                                    faculty_database.removeStudent(student_id);
                                }
                                Faculty* currentFaculty = new Faculty(
                                        faculty_database.get(advisor_ID));
                                currentFaculty->AddStudent(student_id);
                                faculty_database.deleteValue(advisor_ID);
                                faculty_database.insert(*currentFaculty);
                            }
                            else if (faculty_database.get(advisor_ID).getStudentIDList().findDuplicateData(
                                    student_id) > 0
                                    && !student_database.isContains(
                                            student_id))
                            {
                                cout << "Stored duplicate advisor -"
                                        " New ID for " << student_name
                                        << " \n";
                                cout << "Valid IDs to assign: \n";
                                faculty_database.get(advisor_ID).getStudentIDList().printList();
                                while (faculty_database.get(advisor_ID).getStudentIDList().findDuplicateData(
                                        student_id) > 0
                                        && !student_database.isContains(
                                                student_id))
                                    student_id = getIDNumber();
                                Faculty* currentFaculty = new Faculty(
                                        faculty_database.get(advisor_ID));
                                currentFaculty->AddStudent(student_id);
                                faculty_database.deleteValue(advisor_ID);
                                faculty_database.insert(*currentFaculty);
                            }
                            else if (!(faculty_database.get(advisor_ID).getStudentIDList().findDuplicateData(
                                    student_id) > 0)
                                    && student_database.isContains(student_id))
                            {
                                cout
                                        << "Student ID is duplicated. Please Enter new ID for "
                                        << student_name << " \n";
                                faculty_database.get(advisor_ID).getStudentIDList().printList();
                                while (faculty_database.get(advisor_ID).getStudentIDList().findDuplicateData(
                                        student_id) > 0
                                        && !student_database.isContains(
                                                student_id))
                                    student_id = getIDNumber();
                                Faculty* updatedNext = new Faculty(
                                        faculty_database.get(advisor_ID));
                                updatedNext->AddStudent(student_id);
                                faculty_database.deleteValue(advisor_ID);
                                faculty_database.insert(*updatedNext);
                            }
                        }
                        else // faculty member does not exist
                        {
                            while (!(faculty_database.isContains(advisor_ID)))
                            {
                                cout << "Faculty member " << advisor_ID
                                        << " does not exist" << endl
                                        << "Enter a valid faculty ID below:\n";
                                faculty_database.printTree();
                                advisor_ID = getIDNumber();
                            }
                            Faculty* currentFaculty = new Faculty(
                                    faculty_database.get(advisor_ID));
                            currentFaculty->AddStudent(student_id);
                            faculty_database.deleteValue(advisor_ID);
                            faculty_database.insert(*currentFaculty);
                        }
                        Student* new_student = new Student(student_name,
                                                           student_id,
                                                           student_level,
                                                           student_major,
                                                           advisor_ID,
                                                           student_gpa);
                        student_database.insert(*new_student);
                    }
                    field_counter++;
                    // Reset the counter.
                    if (field_counter > 5)
                    {
                        field_counter = 0;
                    }
                }
                if (inputFile.bad())
                {
                    throw Error("Look like some issue with input file");
                }
                else if (!inputFile.eof())
                {
                    throw Error(
                            "The database file stored with invalid format");
                }
                else if (field_counter != 0)
                {
                    throw Error(
                            "Interrupted database file. Please check again.");
                }
            }
        }
        if (inputFile.is_open())
        {
            inputFile.close();
        }
        else
        {
            cout << "DEBUG: Database file didn't exist. Create new one: "
                    << STUDENT_TABLE_NAME << "...\n";

            std::ofstream output(STUDENT_TABLE_NAME, std::ios::out);
            if (!output.is_open())
            {
                throw Error(
                        "Can not open to write file. Please check your system");
            }
            else if (output.is_open())
            {
                output.close();
            }
        }
        cin.clear();
    }
    catch (Error &e)
    {
        cout << e.what() << "\n";
        cout << "Exiting\n";
        throw e;
    }
}

//1. Print all students and their information (sorted by ascending id #)
void DatabaseSystem::PrintAllStudents() const
{

    if (!student_database.isEmpty())
        student_database.printTree();
    else
        cout << "\nNo Students to print\n\n";
}

//2. Print all faculty and their information (sorted by ascending id #)
void DatabaseSystem::PrintAllFalculty() const
{
    if (!faculty_database.isEmpty())
        faculty_database.printTree();
    else
        cout << "\nNo Advisors\n\n";
}

//3. Find and display student information given the students id
void DatabaseSystem::FindAndDisplayStudent(int IDnum) const
{
    if (student_database.isContains(IDnum))
        student_database.get(IDnum).printInfo();
    else
        cout << "\nStudent does not exist\n\n";
}

//4. Find and display faculty information given the faculty id
void DatabaseSystem::FindAndDisplayFaculty(int IDnum) const
{
    if (faculty_database.isContains(IDnum))
        faculty_database.get(IDnum).printInfo();
}

//5. Given a student’s id, print the name and info of their faculty advisor
void DatabaseSystem::FindAndDisplayStudentsAdvisor(int IDnum) const
{
    if (student_database.isContains(IDnum))
    {
        int advisorID = student_database.get(IDnum).getAdvisorID();
        FindAndDisplayFaculty(advisorID);
    }
}

//6. Given a faculty id, print ALL the names and info of his/her advisees.
void DatabaseSystem::FindAndDisplayAdvisorsStudents(int IDnum) const
{

    if (!faculty_database.isEmpty())
    {
        DoublyLinkedList<int>* studIDs = new DoublyLinkedList<int>(
                faculty_database.get(IDnum).getStudentIDList());
        if (!studIDs->isEmpty())
        {
            int DLLsize;
            DLLsize = studIDs->getSize() - 1;
            while (DLLsize != -1)
            {
                //return the position in the DLL
                int ID = studIDs->getDataAtPosition(DLLsize);

                FindAndDisplayStudent(ID);
                --DLLsize;
            }
        }
        else
            cout << "No current Students" << endl;
        ;
        delete studIDs;
    }
}

//7. Add a new student
void DatabaseSystem::AddStudent()
{
    string name, level, major;
    int ID, advisorID;
    double GPA = -1.0;
    string str;
    cout << "Student ID -";
    ID = getIDNumber();
    while (student_database.isContains(ID))
    {
        cout << "Student ID currently in use\n";
        cout << "Student ID -";
        ID = getIDNumber();
        cin.clear();
    }
    cin.clear();
    cout << "Enter Student Name: ";
    getline(cin, str);
    cin.clear();
    name = str;
    cout << "Enter Student Level (Freshman, Sophomore, etc): ";
    getline(cin, str);
    cin.clear();
    level = str;
    cout << "Enter Student Major: ";
    getline(cin, str);
    cin.clear();
    major = str;
    cout << "Enter Student GPA: ";
    while (GPA <= 0 || GPA >= 5.0)
    {
        getline(cin, str);
        cin.clear();
        GPA = strToDouble(str);
        if (GPA <= 0.0 || GPA >= 5.0)
        {
            cout << "GPA MUST be between 0.0 and 5.0\n";
            cout << "Enter Student GPA: ";
        }
    }

    cout << "Advisor ID - ";
    advisorID = getIDNumber();
    cin.clear();
    while (!(faculty_database.isContains(advisorID)))
    {
        cout << "Faculty member " << advisorID << " does not exist...\n"
                << "Enter a valid advisor ID.\nValid Faculty Members Listed: \n";
        faculty_database.printTree();
        advisorID = getIDNumber();
        cin.clear();
    }
    cin.clear();

    if (faculty_database.isContains(advisorID))
    {
        if (faculty_database.get(advisorID).ContainsStudent(ID)
                && !student_database.isContains(ID)
                && !(faculty_database.get(advisorID).getStudentIDList().findDuplicateData(
                        ID) > 0))
        {
            Faculty* updatedNext = new Faculty(
                    faculty_database.get(advisorID));
            updatedNext->AddStudent(ID);
            faculty_database.deleteValue(advisorID);
            faculty_database.insert(*updatedNext);
        }
        else if (!faculty_database.get(advisorID).ContainsStudent(ID)
                && !student_database.isContains(ID)
                && !(faculty_database.get(advisorID).getStudentIDList().findDuplicateData(
                        ID) > 0))
        {
            Faculty* updatedNext = new Faculty(
                    faculty_database.get(advisorID));
            updatedNext->AddStudent(ID);
            faculty_database.deleteValue(advisorID);
            faculty_database.insert(*updatedNext);
        }
        else if (faculty_database.get(advisorID).getStudentIDList().findDuplicateData(
                ID) > 0 && !student_database.isContains(ID))
        {
            cout << "Duplicate ID For Advisor - Enter new ID for " << name
                    << " \n";
            cout << "NON-valid IDs to assign: \n";
            faculty_database.get(advisorID).getStudentIDList().printList();
            while (faculty_database.get(advisorID).getStudentIDList().findDuplicateData(
                    ID) > 0 && !student_database.isContains(ID))
                ID = getIDNumber();
            Faculty* updatedNext = new Faculty(
                    faculty_database.get(advisorID));
            updatedNext->AddStudent(ID);
            faculty_database.deleteValue(advisorID);
            faculty_database.insert(*updatedNext);
        }
        else if (!(faculty_database.get(advisorID).getStudentIDList().findDuplicateData(
                ID) > 0) && student_database.isContains(ID))
        {
            cout << "Duplicate Student Tree ID - Enter new ID for " << name
                    << " \n";
            faculty_database.get(advisorID).getStudentIDList().printList();
            while (faculty_database.get(advisorID).getStudentIDList().findDuplicateData(
                    ID) > 0 && !student_database.isContains(ID))
                ID = getIDNumber();
            Faculty* updatedNext = new Faculty(
                    faculty_database.get(advisorID));
            updatedNext->AddStudent(ID);
            faculty_database.deleteValue(advisorID);
            faculty_database.insert(*updatedNext);
        }
    }
    else
    {
        while (!(faculty_database.isContains(advisorID)))
        {
            cout << "Faculty member " << advisorID << " does not exist...\n"
                    << "Enter a valid advisor ID.\n"
                            " Valid Faculty Members Listed: \n";
            faculty_database.printTree();
            advisorID = getIDNumber();

        }
        Faculty* updatedNext = new Faculty(faculty_database.get(advisorID));
        updatedNext->AddStudent(ID);
        faculty_database.deleteValue(advisorID);
        faculty_database.insert(*updatedNext);

    }

    Student* stud = new Student(name, ID, level, major, advisorID, GPA);
    student_database.insert(*stud);
    delete stud;
}

//8. Delete a student given the id
void DatabaseSystem::DeleteStudent(int IDnum)
{
    if (!faculty_database.isEmpty() && student_database.isContains(IDnum))
    {
        for (int i(faculty_database.getMax()->data.getID()); i >= 0; --i)
        {
            if (faculty_database.isContains(i))
            {
                if (faculty_database.get(i).ContainsStudent(IDnum))
                {
                    Faculty *temp = new Faculty(faculty_database.get(i));
                    temp->RemoveStudent(IDnum);
                    faculty_database.deleteValue(temp->getID());
                    faculty_database.insert(*temp);
                    break;
                }
            }
        }
    }
    if (student_database.isContains(IDnum))
        student_database.deleteValue(IDnum);
}

//9. Add a new faculty member
void DatabaseSystem::AddFacultyMember()
{
    string faculty_name, faculty_level, faculty_department;
    int ID;

    string str;
    cout << "Advisor ID - ";
    ID = getIDNumber();
    cin.clear();
    while (faculty_database.isContains(ID))
    {
        cout << "Faculty member " << ID
                << " already exists.\nEnter a valid advisor ID.\n"
                        "Invalid Faculty Members Listed: \n";
        faculty_database.printTree();
        ID = getIDNumber();
        cin.clear();
    }
    currUndo.SaveState(student_database, faculty_database);
    cout << "Enter Advisor Name: ";
    getline(cin, str);
    cin.clear();
    faculty_name = str;
    cout
            << "Enter Advisor Level (lecturer, assistant prof, associate prof, etc): ";
    getline(cin, str);
    cin.clear();
    faculty_level = str;
    cout << "Enter Advisor Department: ";
    getline(cin, str);
    cin.clear();
    faculty_department = str;

    if (!faculty_database.isContains(ID))
    {
        Faculty *temp = new Faculty(faculty_name, ID, faculty_level,
                                    faculty_department);
        currUndo.SaveState(student_database, faculty_database);
        faculty_database.insert(*temp);
    }
    else
    {
        cout << "ID already exists in database\n";
    }
}

//10. Delete a faculty member given the id.
void DatabaseSystem::DeleteFacultyMember(int IDnum)
{
    if (faculty_database.isContains(IDnum))
    {
        int replaceAdvisorID = -1000;
        if (faculty_database.get(IDnum).getStudentIDList().getSize() > 0)
        {
            while (replaceAdvisorID != -1)
            {
                cout << "Replacement AdvisorID...\n";
                replaceAdvisorID = getIDAbort();

                if (replaceAdvisorID >= 1)
                {
                    if (faculty_database.isContains(replaceAdvisorID))
                    {
                        break;
                    }
                }
            }
            if (replaceAdvisorID != -1)
            {
                DoublyLinkedList<int>* studIDs = new DoublyLinkedList<int>(
                        faculty_database.get(IDnum).getStudentIDList());
                int DLLsize;
                DLLsize = studIDs->getSize() - 1;
                while (DLLsize != -1)
                {
                    int ID = studIDs->getDataAtPosition(DLLsize);
                    ChangeStudentAdvisor(ID, replaceAdvisorID);
                    --DLLsize;
                }
                delete studIDs;

            }
        }
        if (replaceAdvisorID != -1)
        {
            faculty_database.deleteValue(IDnum);
        }
    }
    else
        cout << "Faculty member does not exist...\n";
}

//11. Change a student’s advisor given the student id and the new faculty id.
void DatabaseSystem::ChangeStudentAdvisor(int StudentID, int FacultyID)
{
    if (student_database.isContains(StudentID)
            && faculty_database.isContains(FacultyID)
            && !faculty_database.get(FacultyID).ContainsStudent(StudentID))
    {
        int studPrevAdvisorID = student_database.get(StudentID).getAdvisorID();
        if (faculty_database.isContains(studPrevAdvisorID)
                && studPrevAdvisorID != FacultyID)
        {
            Faculty* updated = new Faculty(
                    faculty_database.get(studPrevAdvisorID));
            updated->RemoveStudent(StudentID);
            faculty_database.deleteValue(studPrevAdvisorID);
            faculty_database.insert(*updated);
            delete updated;
        }
        if (!faculty_database.get(FacultyID).ContainsStudent(StudentID))
        {
            Faculty* updatedNext = new Faculty(
                    faculty_database.get(FacultyID));
            updatedNext->AddStudent(StudentID);
            faculty_database.deleteValue(FacultyID);
            faculty_database.insert(*updatedNext);
            Student* updatedStudent = new Student(
                    student_database.get(StudentID));
            updatedStudent->setAdvisor(FacultyID);
            student_database.deleteValue(StudentID);
            student_database.insert(*updatedStudent);
        }
    }
}

//12. Remove an advisee from a faculty member given the ids
void DatabaseSystem::RemoveStudentFromFacultyRef(int StudentID, int FacultyID)
{
    if (studentInFacultyList(StudentID, FacultyID))
    {
        currUndo.SaveState(student_database, faculty_database);
        cout << "Removing Student ID: " << StudentID
                << " from faculty member ID: " << FacultyID << "\n";
        Faculty *temp = new Faculty(faculty_database.get(FacultyID));
        temp->RemoveStudent(StudentID);
        faculty_database.deleteValue(temp->getID());
        faculty_database.insert(*temp);
        delete temp;
        Student *tempStud = new Student(student_database.get(StudentID));
        tempStud->setAdvisor(-1);
        student_database.deleteValue(StudentID);
        student_database.insert(*tempStud);
    }
    else
    {
        cout << "Student ID or Faculty Member not found\n";
    }
}

//13. Rollback
void DatabaseSystem::RollBack()
{
    cout << "Rolling Back...\n";
    cout << "Restored Trees:\n";
    if (currUndo.CanUndo())
    {
        faculty_database.deleteTree();
        faculty_database = currUndo.GetLastFacultyTree();
        faculty_database.printTree();
        student_database.deleteTree();
        student_database = currUndo.GetLastStudentTree();
        student_database.printTree();
        currUndo.removeLastState();

    }
}
//=============================================
//=============================================
//14. Exit - save data to file
void DatabaseSystem::Exit()
{
    std::ofstream outputFac(FACULTY_TABLE_NAME, std::ios::out);
    if (!outputFac.is_open())
    {
        throw Error("Can not open file");
    }
    else if (outputFac.is_open())
    {
        outputFac << faculty_database.toString();
        outputFac.close();
    }
    std::ofstream outputStud(STUDENT_TABLE_NAME, std::ios::out);
    if (!outputStud.is_open())
    {
        throw Error(" Can not open file");
    }
    else if (outputStud.is_open())
    {
        outputStud << student_database.toString();
        outputStud.close();
    }
}

bool DatabaseSystem::studentInFacultyList(int studID, int facID)
{
    bool found = false;
    if (!faculty_database.isEmpty() && faculty_database.isContains(facID))
    {
        DoublyLinkedList<int>* studIDs = new DoublyLinkedList<int>(
                faculty_database.get(facID).getStudentIDList());
        if (studIDs->findData(studID) != -1)
        {
            found = true;
        }
        else
        {
            cout << "Student ID not linked to a faculty member\n";
        }
        delete studIDs;
    }
    else
    {
        cout << "Faculty member does not exist\n";
    }
    return found;
}
