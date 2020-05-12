/*
 * GenStack.h
 *
 */

#ifndef GENSTACK_H_
#define GENSTACK_H_

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <stdio.h>

const unsigned int ARR_MAX = 6;
const int STACK_INDEX_VAL = -1;

using namespace std;
template<typename T>
class GenStack {
public:
    GenStack() :
            size_stack(ARR_MAX), num_element(0), top_element(-1) // default constructor
    {
        array_data = new T[size_stack];
    }
    GenStack(unsigned int sz) :
            size_stack(sz), num_element(0), top_element(-1) {
        array_data = new T[size_stack];
    }
    ~GenStack() {
        delete[] array_data;
    }

    void push(T d) {
        if (!isFull()) {
            array_data[++top_element] = d;
            num_element++;
        } else {
            resizeLarger();
            array_data[++top_element] = d;
            num_element++;
        }
    }
    void push(T* d) {
        if (!isFull()) {
            array_data[++top_element] = *d;
            num_element++;
        } else {
            resizeLarger();
            array_data[++top_element] = *d;
            num_element++;
        }
    }
    T pop() {
        try {
            if (isEmpty())
                throw runtime_error("Error: Can not pop from empty stack\n");
            num_element--;
            return array_data[top_element--];
        } catch (runtime_error &e) {
            cout << e.what();
            throw e;
        }
    }

    T top() const
    {
        try {
            if (isEmpty())
                throw runtime_error("Error: No items in stack\n");
            return array_data[top_element];
        } catch (runtime_error &e) {
            cout << e.what();
            throw e;
        }
    }
    bool isFull() const {
        return (num_element == size_stack - 1);
    }
    bool isEmpty() const {
        return (num_element == 0);
    }
    unsigned int getSize() {
        return num_element;
    }
    unsigned int getSizeM() {
        return size_stack;
    }

private:
    void resizeLarger() {
        T* tempArr = new T[size_stack + ARR_MAX];
        copy(array_data, array_data + size_stack, tempArr);
        size_stack += ARR_MAX - 1;
        swap(array_data, tempArr);
        delete[] tempArr;
    }
    void resizeSmaller() {
        T* tempArr = new T[num_element + 1];
        copy(array_data, array_data + num_element + 1, tempArr);
        size_stack = num_element + 1;
        swap(array_data, tempArr);
        delete[] tempArr;
    }
    unsigned int size_stack;
    int top_element;
    T* array_data;
    int num_element;
};

#endif /* GENSTACK_H_ */
