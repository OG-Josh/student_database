/*
 * FileHandler.h
 *
 *  Created on: May 12, 2020
 *      Author: Johnny
 *      Email: johnnytuot@gmail.com
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <fstream>
#include <iostream>
#include <string>


using namespace std;

class FileHandler {
public:
    ~FileHandler() {
    }
    ;
    bool open(ifstream& inFile, string fileName);
    bool isEmptyFile(ifstream& inFile);
    bool isWhiteSpace(const string &str);
    void close();

    ifstream* getReadFD() {
        return input_file;
    }
    ofstream* getWriteFD() {
        return output_file;
    }
private:
    ifstream* input_file;
    ofstream* output_file;
    int a;
};

#endif /* FILEHANDLER_H_ */
