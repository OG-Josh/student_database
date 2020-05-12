/*
 * Faculty.cpp
 *
 */
#include <iostream>
#include "Faculty.h"

bool operator==(const Faculty &c1, const Faculty &c2)
{
    return c1.getID() == c2.getID();
}
bool operator!=(const Faculty &c1, const Faculty &c2)
{
    return !(c1 == c2);
}
bool operator>(const Faculty &c1, const Faculty &c2)
{
    return c1.getID() > c2.getID();
}
bool operator<(const Faculty &c1, const Faculty &c2)
{
    return c1.getID() < c2.getID();
}
bool operator==(const int &c2, const Faculty &c1)
{
    return c2 == c1.getID();
}
bool operator!=(const int &c2, const Faculty &c1)
{
    return !(c2 == c1);
}
bool operator>(const int &c2, const Faculty &c1)
{
    return c2 > c1.getID();
}
bool operator<(const int &c2, const Faculty &c1)
{
    return c2 < c1.getID();
}

bool operator==(const Faculty &c1, const int &c2)
{
    return c1.getID() == c2;
}
bool operator!=(const Faculty &c1, const int &c2)
{
    return !(c1 == c2);
}
bool operator>(const Faculty &c1, const int &c2)
{
    return c1.getID() > c2;
}
bool operator<(const Faculty &c1, const int &c2)
{
    return c1.getID() > c2;
}

ostream& operator <<(ostream& out, const Faculty& faculty)
{
    if (out.rdbuf() == cout.rdbuf())
    {
        out << faculty.getID() << " | " << faculty.getName() << " | "
                << faculty.getLevel() << " | " << faculty.getDepartment()
                << " | " << faculty.getStudentIDList().printListToString();
    }
    else
    {
        out << "ID: " << faculty.getID() << "\nName: " << faculty.getName()
                << "\nOccupation: " << faculty.getLevel() << "\nDepartment: "
                << faculty.getDepartment() << "\n|"
                << faculty.getStudentIDList().printListToString() << "|\n";
    }

    return out;
}

