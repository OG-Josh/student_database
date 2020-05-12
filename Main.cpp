/*
 * Main.cpp
 *
 */

#include <iostream>

#include "DatabaseSystem.h"
#include "Utility.h"

using std::cout;

int main(int argc, const char * argv[]) {
    try {
        DatabaseSystem *database_system = new DatabaseSystem();
        database_system->readFacultyDatabaseFromFile();
        database_system->readStudentDatabaseFromFile();
        database_system->running();
        delete database_system;
    } catch (Error &e) {
        return EXIT_FAILURE;
    } catch (...) {
        cout << "Unknown exception" << endl;
        return 2;
    }
    return 0;

}

