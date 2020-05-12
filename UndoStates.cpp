/*
 * UndoStates.cpp
 *
 */

#include <iostream>
using std::cout;

#include "UndoStates.h"

bool UndoStates::CanUndo() {
    if (states.top() == None)
        cout << "\nNothing to Undo...\n";
    return states.top() != None;
}

void UndoStates::SaveState(BST<Student> studCopy, BST<Faculty> facCopy) {
    BST<Student> tempStud(studCopy);
    studentTreeCopy.push(tempStud);
    facultyTreeCopy.push(facCopy);
    states.push(ChangedState);
}

int UndoStates::GetLastAction() {
    return states.top();
}
BST<Student> UndoStates::GetLastStudentTree() {
    return studentTreeCopy.pop();
}
BST<Faculty> UndoStates::GetLastFacultyTree() {

    return facultyTreeCopy.pop();
}
void UndoStates::removeLastState() {
    states.pop();
}

