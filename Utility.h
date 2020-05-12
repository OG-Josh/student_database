/*
 * Utility.h
 *
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdexcept>
#include <string>
#include <sstream>
#include <limits.h>
using namespace std;

class Error: public runtime_error {
public:
    Error() :
            runtime_error("Something Bad Happened...") {
    }
    Error(string msg) :
            runtime_error(msg.c_str()) {
    }
private:

};


#endif /* UTILITY_H_ */
