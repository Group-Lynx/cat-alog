#include "Node.h"

template <typename T>
Node<T>::Node(T _value)
{
    last = nullptr;
    next = nullptr;
    value = new T(_value);
}

// template <typename T>
// Node<T>::Node(T* _valuePtr)
// {
//     last = nullptr;
//     next = nullptr;
//     value = _valuePtr;
// }

template <typename T>
Node<T>::~Node()
{
    delete value;
}

class User;
class Course;
class Student;
class Teacher;

template class Node<User>;
template class Node<Course>;
template class Node<Student>;
template class Node<Teacher>;
