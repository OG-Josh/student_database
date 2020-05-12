/*
 * FileHandler.cpp
 *
 *  Created on: May 12, 2020
 *      Author: Johnny
 *      Email: johnnytuot@gmail.com
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Utility.h"
#include "FileHandler.h"

using namespace std;

bool FileHandler::open(ifstream& inFile, string fileName) {
    try {
        inFile.open(fileName, ios::in);
        if (inFile.is_open()) {
            // uncomment below to show filename and success during runtime
            //cout << "File: <" << fileName << "> opened successfully...\n";
            input_file = &inFile;
            return true;
        }
        inFile.close();
        //throw Error ("File Not Found\n");
        return false;
    } catch (Error &e) {
        throw e;
    }
}

bool FileHandler::isEmptyFile(ifstream& inFile) {
    return inFile.peek() == ifstream::traits_type::eof();
}

bool FileHandler::isWhiteSpace(const string &str) {
    return str.find_first_not_of(' ') != string::npos;
}

void FileHandler::close() {
    input_file->close();
}

