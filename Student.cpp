/*
 * Student.cpp
 *
 */

#include <iostream>
#include "Student.h"
using std::ostream;

// compare to other student
bool operator==(const Student &c1, const Student &c2) {
    return c1.getID() == c2.getID();
}
bool operator!=(const Student &c1, const Student &c2) {
    return !(c1 == c2);
}
bool operator>(const Student &c1, const Student&c2) {
    return c1.getID() > c2.getID();
}
bool operator<(const Student &c1, const Student&c2) {
    return c1.getID() < c2.getID();
}

// compare to integer
bool operator==(const int &c2, const Student &c1) {
    return c2 == c1.getID();
}
bool operator!=(const int &c2, const Student &c1) {
    return !(c2 == c1);
}
bool operator>(const int &c2, const Student &c1) {
    return c2 > c1.getID();
}
bool operator<(const int &c2, const Student &c1) {
    return c2 < c1.getID();
}

bool operator==(const Student &c1, const int &c2) {
    return c1.getID() == c2;
}
bool operator!=(const Student &c1, const int &c2) {
    return !(c1 == c2);
}
bool operator>(const Student &c1, const int &c2) {
    return c1.getID() > c2;
}
bool operator<(const Student &c1, const int &c2) {
    return c1.getID() < c2;
}

ostream& operator <<(ostream& out, const Student& student) {
    if (out.rdbuf() == cout.rdbuf()) {
        out << student.getID() << " | " << student.getName() << " | " << student.getLevel() << " | " << student.student_gpa << " | " << student.student_advisor;
    } else {
        out << student.getID() << "\n" << student.getName() << "\n"
                << student.getLevel() << "\n" << student.student_major << "\n"
                << student.student_gpa << "\n" << student.student_advisor << "\n";
    }
    return out;
}

