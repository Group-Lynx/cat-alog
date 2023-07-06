#ifndef NODE_H
#define NODE_H

#include <memory>

// == ÉùÃ÷ == //

template <typename T>
class Node
{
public:
    std::shared_ptr<Node<T>> last;
    std::shared_ptr<Node<T>> next;
    std::unique_ptr<T> value;

public:
    Node();
    Node(T _value);
    ~Node();
};

// == ¶¨Òå == //

template <typename T>
Node<T>::Node()
{
    last = nullptr;
    next = nullptr;
    value = nullptr;
}

template <typename T>
Node<T>::Node(T _value)
{
    last = nullptr;
    next = nullptr;
    value = std::make_unique<T>(_value);
}

template <typename T>
Node<T>::~Node() = default;

#endif