/*
 * Person.h
 *
 *  The base class. The Student and Faculty will be inherited from this
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>
using std::string;
class Person {
public:
    Person(string name, int ID, string level) :
            name(name), ID(ID), level(level) {
    }

    virtual ~Person() {
    }

    Person(const Person& source) {

        this->name = source.name;
        this->ID = source.ID;
        this->level = source.level;

    }

    virtual void printInfo() = 0;

    string getName() const {
        return name;
    }
    int getID() const {
        return ID;
    }
    string getLevel() const {
        return level;
    }

private:
    string name;
    int ID;
    string level;
};

#endif /* PERSON_H_ */
