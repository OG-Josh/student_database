/*
 * UndoStates.h
 *
 */

#ifndef UNDOSTATES_H_
#define UNDOSTATES_H_

#include "BST.h"
#include "GenStack.h"
#include "Person.h"
#include "Student.h"
#include "Faculty.h"

class UndoStates {

    enum EnumStates {
        None, ChangedState
    };

public:
    UndoStates() {

        states.push(None);
    }
    ~UndoStates() {
        ;
    }

    bool CanUndo();

    void SaveState(BST<Student> studCopy, BST<Faculty> facCopy);

    int GetLastAction();
    BST<Student> GetLastStudentTree();
    BST<Faculty> GetLastFacultyTree();
    void removeLastState();

private:

    GenStack<BST<Student> > studentTreeCopy;
    GenStack<BST<Faculty> > facultyTreeCopy;

    GenStack<int> states;

};

#endif /* UNDOSTATES_H_ */
