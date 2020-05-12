/*
 * BTS.h
 *
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>

#include "DoublyLinkedList.h"
#include "Utility.h"
#include "Faculty.h"
#include "Student.h"

using std::cout;
template <class T>
class BSTNode
{
    public:
        BSTNode() :
                data(NULL), left_node(nullptr), right_node(nullptr)
        {
        }
        ;
        BSTNode(T key) :
                data(key), left_node(nullptr), right_node(nullptr)
        {
        }
        ;
        BSTNode(const BSTNode<T> &other) :
                data(other.data)
        {
        }
        void operator =(BSTNode &other)
        {
            if (other == NULL)
                this->data = other->data;
        }
        virtual ~BSTNode()
        {
            left_node = nullptr;
            right_node = nullptr;
        }

        T data;
        BSTNode *left_node;
        BSTNode *right_node;
    private:
};

template <class U>
class BST
{
    public:
        BST() :
                root_node(nullptr)
        {
        }

        ~BST()
        {
            deleteTreeHelper(&root_node);
        }

        // Copy constructor
        BST(BST<U> const &other)
        {
            if (other.root_node == NULL)
                root_node = NULL;
            else
            {
                BSTNode<U> * copy;
                copy = other.root_node;
                root_node = copyHelper(root_node, copy);
            }

        }

    private:
        // Helper function copy node from other
        BSTNode<U>* copyHelper(BSTNode<U> * toNode, BSTNode<U>*& fromNode)
        {
            if (fromNode == nullptr)
            {
                toNode = nullptr;
            }
            else
            {
                toNode = new BSTNode<U>(*fromNode);
                toNode->left_node = copyHelper(toNode->left_node,
                                               fromNode->left_node);
                toNode->right_node = copyHelper(toNode->right_node,
                                                fromNode->right_node);
            }
            return toNode;
        }

    public:
        // Operator equal
        BST &operator =(const BST<U> &other)
        {
            if (other.root_node == NULL)
                root_node = NULL;
            else
            {
                BSTNode<U> * tmp = other.root_node;
                root_node = copyHelper(root_node, tmp);
            }
            return *this;
        }

        void operator =(BST<U> *other)
        {
            if (other->root_node == NULL)
                root_node = NULL;
            else
                root_node = copyHelper(this->root_node, other->root_node);
        }

        // Insert value to node
        void insert(U data_value)
        {
            BSTNode<U> *new_node = new BSTNode<U>(data_value);
            if (isEmpty())
            {
                root_node = new_node;
            }
            else
            {
                BSTNode<U>* current_node = root_node;
                BSTNode<U>* parent_node = nullptr;
                while (true)
                {
                    if (data_value < current_node->data)
                    {
                        // Traverse to left
                        parent_node = current_node;
                        current_node = current_node->left_node;
                        if (current_node == nullptr)
                        {
                            parent_node->left_node = new_node;
                            break;
                        }
                    }
                    else if (data_value > current_node->data)
                    {
                        // Traverse to right
                        parent_node = current_node;
                        current_node = current_node->right_node;
                        if (current_node == nullptr)
                        {
                            parent_node->right_node = new_node;
                            break;
                        }
                    }
                    else if (data_value == current_node->data)
                    {
                        cout << "Key with value : " << data_value
                                << " is duplicated. Please check your BST!!!!!";
                        break;
                    }
                }
            }
        }

        // Check data is contain in the tree or not
        bool isContains(U data_value) const
        {
            if (isEmpty())
                return false;
            BSTNode<U>* current_node = root_node;
            while (current_node->data != data_value)
            {
                if (data_value < current_node->data)
                    current_node = current_node->left_node;
                else
                    current_node = current_node->right_node;
                if (current_node == nullptr)
                    return false;
            }
            return true;
        }

        bool isContains(int value) const
        {
            if (isEmpty())
                return false;
            BSTNode<U>* current = root_node;
            while (current->data != value)
            {
                if (value < current->data)
                    current = current->left_node;
                else
                    current = current->right_node;
                if (current == nullptr)
                    return false;
            }
            return true;
        }

        // get node with value
        U get(int value) const
        {
            if (isEmpty())
                return root_node->data;

            BSTNode<U>* current = root_node;
            while (current->data != value)
            {
                if (value < current->data)
                    current = current->left_node;
                else
                    current = current->right_node;

                if (current == nullptr) // value not in tree
                    return root_node->data;
            }
            return current->data;
        }

        // delete node
        U deleteValue(U k)
        {
            if (!isContains(k))
            {
                throw Error("Key not found in tree\n");
            }
            if (isEmpty())
                throw Error("Tree is empty.!!!!!");
            BSTNode<U>* current_node = root_node;
            BSTNode<U>* parent_node = root_node;

            bool in_left_node = true;
            while (current_node->data != k)
            {
                parent_node = current_node;
                if (k < current_node->data)
                {
                    in_left_node = true;
                    current_node = current_node->left_node;
                }
                else
                {
                    in_left_node = false;
                    current_node = current_node->right_node;
                }
                if (current_node == nullptr)
                    return root_node->data;
            }
            if (current_node->left_node == nullptr
                    && current_node->right_node == nullptr)
            {
                if (current_node == root_node)
                {
                    root_node = nullptr;
                }
                else if (in_left_node)
                {
                    parent_node->left_node = nullptr;
                }
                else
                    parent_node->right_node = nullptr;
            }
            else if (current_node->right_node == nullptr)
            {
                if (current_node == root_node)
                {
                    root_node = current_node->left_node;
                }
                else if (in_left_node)
                {
                    parent_node->left_node = current_node->left_node;
                }
                else
                {
                    parent_node->right_node = current_node->left_node;
                }
            }
            else if (current_node->left_node == nullptr)
            {
                if (current_node == root_node)
                {
                    root_node = current_node->right_node;
                }
                else if (in_left_node)
                {
                    parent_node->left_node = current_node->right_node;
                }
                else
                {
                    parent_node->right_node = current_node->right_node;
                }
            }
            else
            {
                BSTNode<U> *successor = getSuccessor(current_node);
                if (current_node == root_node)
                    root_node = successor;
                else if (in_left_node)
                    parent_node->left_node = successor;
                else
                    parent_node->right_node = successor;
                successor->left_node = current_node->left_node;
            }
            U *temp = current_node->data;
            delete current_node;
            return temp;
        }

        U deleteValue(int k)
        {
            if (isEmpty())
                throw(Error("No Values"));
            BSTNode<U>* current_node = root_node;
            BSTNode<U>* parent_node = root_node;
            bool isLeft = true;
            while (k != current_node->data)
            {
                parent_node = current_node;
                if (k < current_node->data)
                {
                    isLeft = true;
                    current_node = current_node->left_node;
                }
                else
                {
                    isLeft = false;
                    current_node = current_node->right_node;
                }
                if (current_node == nullptr)
                    throw(Error("Value Does Not Exist\n"));
            }
            if (current_node->left_node == nullptr
                    && current_node->right_node == nullptr)
            {
                if (current_node == root_node)
                {
                    root_node = nullptr;
                }
                else if (isLeft)
                {
                    parent_node->left_node = nullptr;
                }
                else
                    parent_node->right_node = nullptr;
            }
            else if (current_node->right_node == nullptr)
            {
                if (current_node == root_node)
                {
                    root_node = current_node->left_node;
                }
                else if (isLeft)
                {
                    parent_node->left_node = current_node->left_node;
                }
                else
                {
                    parent_node->right_node = current_node->left_node;
                }
            }
            else if (current_node->left_node == nullptr)
            {
                if (current_node == root_node)
                {
                    root_node = current_node->right_node;
                }
                else if (isLeft)
                {
                    parent_node->left_node = current_node->right_node;
                }
                else
                {
                    parent_node->right_node = current_node->right_node;
                }
            }
            else
            {
                BSTNode<U> *successor = getSuccessor(current_node);
                if (current_node == root_node)
                    root_node = successor;
                else if (isLeft)
                    parent_node->left_node = successor;
                else
                    parent_node->right_node = successor;
                successor->left_node = current_node->left_node;
            }
            U Temp = current_node->data;
            delete current_node;

            return Temp;
        }

        BSTNode<U>* getSuccessor(BSTNode<U>* d)
        {
            BSTNode<U>* successor_parrent = d;
            BSTNode<U>* successor = d;
            BSTNode<U>* current_right_node = d->right_node;

            while (current_right_node != nullptr)
            {
                successor_parrent = successor;
                successor = current_right_node;
                current_right_node = current_right_node->left_node;
            }
            if (successor != d->right_node)
            {
                successor_parrent->left_node = successor->right_node;
                successor->right_node = d->right_node;
            }
            return successor;
        }

        // Get min value of tree
        BSTNode<U>* getMin()
        {
            BSTNode<U>* current_node = root_node;
            while (current_node->left_node != nullptr)
            {
                current_node = current_node->left_node;
            }
            return current_node;
        }

        // Get max
        BSTNode<U>* getMax()
        {
            BSTNode<U>* current_node = root_node;
            while (current_node->right_node != nullptr)
            {
                current_node = current_node->right_node;
            }
            return current_node;
        }

        bool isEmpty() const
        {
            return root_node == nullptr;
        }

    private:
        void printHelper(BSTNode<U>* node) const
        {
            if (node == nullptr)
                return;

            printHelper(node->left_node);
            std::cout << node->data << endl;
            printHelper(node->right_node);
        }

        string toStringHelper(BSTNode<U>* node) const
        {
            string result = "";
            string temp = "";
            if (node == nullptr)
                return result;
            stringstream ss;
            temp = recToString(node->left_node);
            ss << node;
            temp = recToString(node->right_node);

            result += ss.str();
            return result;
        }

        void removeStudentHelper(BSTNode<U>*, int);
    public:

        void printTree() const
        {
            printHelper(root_node);
        }

        string toString()
        {
            string s;
            s = toStringHelper(root_node);
            return s;
        }

        void removeStudent(int studID)
        {
            if (std::is_same<Faculty, U>::value)
                removeStudentHelper(root_node, studID);
        }

        bool hasOneObject() const
        {
            return root_node->right_node == nullptr
                    && root_node->left_node == nullptr;
        }

        void deleteTree()
        {
            deleteTreeHelper(&root_node);
        }

    private:
        BSTNode<U>*root_node;

        // https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/
        void deleteNodeHepler(BSTNode<U>* node)
        {
            if (node == nullptr)
                return;
            deleteNodeHepler(node->left_node);
            deleteNodeHepler(node->right_node);
            delete (node);
        }

        // Deletes a tree and sets the root as NULL
        void deleteTreeHelper(BSTNode<U>** inRoot)
        {
            deleteNodeHepler(*inRoot);
            *inRoot = nullptr;
        }

};

template <>
inline void BST<Student>::printTree() const
{
    cout << "====== All Student: ======" << endl;
    cout << "ID | Name | Level | GPA | Advisor" << endl;
    printHelper(root_node);
    cout << "\n";
}

template <>
inline void BST<Faculty>::printTree() const
{
    cout << "====== All Faculty: ======" << endl;
    cout << "ID | Name | Level | Department | Student List" << endl;
    printHelper(root_node);
    cout << "\n";
}

template <>
inline string BST<Faculty>::toStringHelper(BSTNode<Faculty>* node) const
{
    string result = "";
    string temp = "";
    if (node == nullptr)
        return result;
    stringstream ss;
    result += toStringHelper(node->left_node);
    ss << node->data;
    result += toStringHelper(node->right_node);

    result.append(ss.str());
    return result;
}
template <>
inline string BST<Student>::toStringHelper(BSTNode<Student>* node) const
{
    string result = "";
    string temp = "";
    if (node == nullptr)
        return result;
    stringstream ss;
    result += toStringHelper(node->left_node);
    ss << node->data;
    result += toStringHelper(node->right_node);

    result.append(ss.str());
    return result;
}

template <>
inline bool BST<Student>::isContains(int value) const
{
    if (isEmpty())
        return false;

    BSTNode<Student> *current = root_node;
    while (current->data != value)
    {
        if (value < current->data)
            current = current->left_node;
        else
            current = current->right_node;

        if (current == nullptr) // value not in tree
            return false;
    }
    return true;
}

template <>
inline void BST<Faculty>::removeStudentHelper(BSTNode<Faculty>* node,
        int studID)
{
    if (node == nullptr)
        return;
    removeStudentHelper(node->left_node, studID);
    if (node->data.getStudentIDList().findData(studID) && node != nullptr
            && !node->data.getStudentIDList().isEmpty())
    {
        node->data.RemoveStudent(studID);
    }
    removeStudentHelper(node->right_node, studID);
}

#endif /* BST_H_ */
