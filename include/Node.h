#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
    Node<T>* last;
    Node<T>* next;
    T* value;

public:
    Node(T _value);
    ~Node();
};

#endif