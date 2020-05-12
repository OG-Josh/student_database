/*
 * DoublyLinkedList.h
 *
 */

#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_

#include <iostream>

#include <string>
#include <sstream>

using std::cout;
using std::string;
using std::stringstream;

template <class U>
class Node
{
    public:
        Node() :
                data(0), next(NULL), prev(NULL)
        {
        }
        ;
        Node(U data) :
                data(data), next(0), prev(0)
        {
        }
        ;
        Node(Node<U> *data, Node<U> *n, Node<U>*p) :
                data(data->getData()), next(n), prev(p)
        {
        }
        Node(const Node<U> &other)
        {
            this->data = other.data;
            if (other.next)
            {
                Node<U> *p = new Node<U>(*other.next);
                append(*p);
            }

        }

        void append(Node &n)
        {
            next = &n;
            n.prev = this;
        }

        ~Node()
        {

        }

        Node<U> *next, *prev;
        U getData()
        {
            return data;
        }

        U* getDataptr()
        {
            return *data;
        }

    private:
        U data;
};

template <class U>
class DoublyLinkedList
{
    public:
        DoublyLinkedList() :
                size(0), front(nullptr), back(nullptr)
        {
        }

        ~DoublyLinkedList()
        {
            Node<U>* current = front;

            while (current)
            {
                current->prev = nullptr;
                Node<U>* next = current->next;
                delete current;
                current = next;
            }
            front = back = nullptr;
        }

        DoublyLinkedList(const DoublyLinkedList<U> &source) :
                front(0), back(0), size(0)
        {
            if (source.front != nullptr)
            {
                Node<U>* temp = (source.front);
                while (temp != nullptr)
                {
                    insertFront(temp->getData());
                    temp = temp->next;
                }
            }
        }

        int findDuplicateData(U val) const
        {
            int idx = -1;
            int total = -1;
            Node<U> *curr = front;
            while (curr != nullptr)
            {
                ++idx;
                if (curr->getData() == val)
                {
                    ++total;
                    if (total == 1)
                    {
                        break;
                    }
                    curr = curr->next;
                }
                else
                {
                    curr = curr->next;
                }
            }

            if (curr == nullptr)
                total = -1;
            return total;
        }

        U getFrontData()
        {
            return front->getData();
        }

        U getDataAtPosition(int pos)
        {
            Node<U> *curr = front;
            int idx = 0;
            while (curr != nullptr)
            {

                if (pos == idx)
                {
                    return curr->getData();
                }
                else
                {
                    curr = curr->next;
                }
                ++idx;
            }
            return curr->getData();
        }
        bool isEmpty() const
        {
            return size <= 0;
        }
        unsigned int getSize() const
        {
            return size;
        }
        U removeKey(U key)
        {
            Node<U>* curr = front;
            while (curr->getData() != key)
            {
                curr = curr->next;
                if (curr == nullptr)
                    return NULL;
            }
            if (curr == front)
            {
                front = curr->next;
            }
            else
            {
                curr->prev->next = curr->next;
            }
            if (curr == back)
            {
                back = curr->prev;
            }
            else
            {
                curr->next->prev = curr->prev;
            }
            curr->next = nullptr;
            curr->prev = nullptr;
            U temp = curr->getData();
            delete curr;
            size--;
            return temp;
        }

        int removeIntKey(int key)
        {
            Node<U>* curr = front;
            while (curr->getData() != key)
            {
                curr = curr->next;
                if (curr == nullptr)
                    return -1;
            }
            if (curr == front)
            {
                front = curr->next;
            }
            else
            {
                curr->prev->next = curr->next;
            }
            if (curr == back)
            {
                back = curr->prev;
            }
            else
            {
                curr->next->prev = curr->prev;
            }
            curr->next = nullptr;
            curr->prev = nullptr;
            U temp = curr->getData();
            delete curr;
            size--;
            return temp;
        }

        U deletePos(int pos)
        {
            if (pos > 0)
            {
                int idx = 0;
                Node<U>* curr = front;
                Node<U>* prev = front;
                while (idx != pos)
                {
                    prev = curr;
                    curr = curr->next;
                    ++idx;
                }
                if (idx == pos)
                {
                    prev->next = curr->next;
                    curr->next = nullptr;
                }
                U temp = curr->getData();
                if (idx == pos)
                {
                    delete curr;
                    size--;
                }
                return temp;
            }
            else
            {
                if (front == nullptr || front->next == nullptr)
                    return NULL;
                else
                {
                    Node<U> *temp = front;
                    front = front->next;
                    delete temp;
                    size--;
                    return front->getData();
                }
            }
        }

        void printList()
        {
            Node<U>* curr = front;
            while (curr)
            {
                std::cout << curr->getData() << "\n";
                curr = curr->next;
            }
        }
        string printListToString()
        {
            Node<U>* curr = front;
            std::stringstream ss;
            while (curr)
            {
                if (curr->next != nullptr)
                    ss << curr->getData() << " ";
                else
                    ss << curr->getData();
                curr = curr->next;
            }
            string list(ss.str());
            return list;
        }

        int findData(U val) const
        {
            int idx = -1;
            Node<U> *curr = front;
            while (curr != nullptr)
            {
                ++idx;
                if (curr->getData() == val)
                {
                    break;
                }
                else
                {
                    curr = curr->next;
                }
            }

            if (curr == nullptr)
                idx = -1;
            return idx;
        }
        void insertFront(U data)
        {
            Node<U>* new_node = new Node<U>(data);
            if (isEmpty())
            {
                back = new_node;
            }
            else
            {
                new_node->next = front;
                front->prev = new_node;
            }
            front = new_node;
            size++;
        }

        U removeFront()
        {
            U tmp = front->getData();
            Node<U>* front_node = front;
            if (isEmpty())
            {
                back = nullptr;
            }
            else if (front->next == nullptr)
            {
                front = nullptr;
            }
            else
            {
                front->next->previous == nullptr;
            }
            front = front->next;
            front_node->next = nullptr;
            delete front_node;
            size--;
            return tmp;
        }

        void insertBack(U data)
        {
            Node<U>* node = new Node<U>(data);
            if (isEmpty())
            {
                front = node;
            }
            else
            {
                back->next = node;
                node->prev = back;

            }
            back = node;
            size++;
        }
    private:
        Node<U>* back;
        Node<U>* front;
        unsigned int size;
};

#endif /* DOUBLYLINKEDLIST_H_ */
