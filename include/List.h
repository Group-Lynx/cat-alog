#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <algorithm>
#include <stdexcept>

template <typename T>
class List
{
    friend class Node<T>;

private:
    Node<T>* head;
    Node<T>* tail;
    unsigned int size;
    Node<T>* footprintPtr;
    unsigned int footprintId;

public:
    List();
    ~List();

public:
    bool OutOfBound(unsigned int _index) const;
    unsigned int Length() const;

private:
    Node<T>* ForewardTrace(Node<T>* _entry, unsigned int _offset);
    Node<T>* BackwardTrace(Node<T>* _entry, unsigned int _offset);
    Node<T>* Trace(unsigned int _index);

public:
    void InsertNode(T _tempValue, unsigned int _index);
    void AppendNode(T _value);
    void DeleteNode(unsigned int _index);

public:
    int SeekNode(T _value);

private:
    T& AccessNode(unsigned int _index);
public:
    T& operator[] (int _index);
};

#endif