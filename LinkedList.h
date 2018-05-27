#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
#include <iostream>
#include <stdexcept>
#include <exception>

template <typename T>
class LinkedList
{
  private:
    //Helper class Definition
    template <typename U>
    struct Node
    {
      public:
        U value;
        Node<U> *nextNode = nullptr;

        Node() {}
        Node(U _value, Node<U> *_nextNode = nullptr) : value(_value), nextNode(_nextNode) {}
    };

    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    unsigned size = 0;

    void checkLinkedListIsEmptyAndThrowException()
    {
        if (!head)
            throw std::runtime_error("Linked list is empty.");
    }

  public:
    inline bool isEmpty() const { return !head ? true : false; }

    T &operator[](int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Out of range in operator[] in LinkedList");

        Node<T> *tempNode = head;

        for (size_t i = 0; i < index; i++)
            tempNode = tempNode->nextNode;

        return tempNode->value;
    }

    void push_front(T _value)
    {
        Node<T> *tempNode = new Node<T>(_value);
        tempNode->nextNode = head;
        head = tempNode;

        tail = !size ? head : tail;
        ++size;
    }
    void push_back(T _value)
    {
        Node<T> *tempNode = new Node<T>(_value);
        if (isEmpty())
        {
            head = tempNode;
            tail = head;
        }
        else
        {
            tail->nextNode = tempNode;
            tail = tail->nextNode;
        }

        ++size;
    }

    const T &front()
    {
        return head->value;
    }
    const T &back()
    {
        return tail->value;
    }

    void insert(int index, T _value)
    {
        if (index < 0 || index > size)
            throw std::out_of_range("Given index in insert function is incorrect! Out of range!");
        if (isEmpty())
        {
            if (index != 0)
                throw std::out_of_range("Given index in insert function is incorrect! Out of range!");
            else
            {
                head = new Node<T>(_value);
                tail = head;
                ++size;
                return;
            }
        }

        Node<T> *tempNode;

        if (!index)
        {
            tempNode = new Node<T>(_value, head);
            head = tempNode;
        }
        else
        {
            Node<T> *prevTempNode = nullptr;
            tempNode = head;

            for (int i = 0; i < index; i++)
            {
                prevTempNode = tempNode;
                tempNode = tempNode->nextNode;
            }

            prevTempNode->nextNode = new Node<T>(_value, tempNode);
            tail = index == size ? tail->nextNode : tail;
        }

        ++size;
    }

    void remove(T _value)
    {
        if (isEmpty())
            return;

        Node<T> *tempNode = head,
                *prevNode = nullptr;
        while (tempNode)
        {
            if (tempNode->value == _value)
            {
                //Setting new tail if neccessary
                if (tempNode == tail)
                    tail = prevNode;

                //Removing first node
                if (tempNode == head)
                {
                    tempNode = head->nextNode;
                    delete head;
                    head = tempNode;
                    prevNode = nullptr;
                }
                //Removing any other node
                else
                {
                    prevNode->nextNode = tempNode->nextNode;
                    delete tempNode;
                    tempNode = prevNode->nextNode;
                }

                --size;
                continue;
            }

            prevNode = tempNode;
            tempNode = tempNode->nextNode;
        }
    }

    void clear()
    {
        if (isEmpty())
            return;

        Node<T> *tempNode = head;

        while (tempNode)
        {
            tempNode = tempNode->nextNode;
            delete head;
            head = tempNode;
        }

        size = 0;
        head = tail = nullptr;
    }

    void show()
    {
        if (isEmpty())
        {
            std::cout << "List is empty!";
            return;
        }

        Node<T> *tempNode = head;
        std::cout << "List: " << std::endl;

        while (tempNode)
        {
            std::cout << tempNode->value << "\t";
            tempNode = tempNode->nextNode;
        }

        std::cout << std::endl;
    }
};

#endif