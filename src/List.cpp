#include "List.h"

template <typename T>
List<T>::List()
{
    head = new Node<T> (0);
    tail = new Node<T> (0);
    head->next = tail;
    tail->last = head;
    size = 0;
    footprintPtr = head;
    footprintId = 0;
}

template <typename T>
List<T>::~List()
{
    Node<T>* previous = nullptr;
    Node<T>* current = head;
    while (current != nullptr)
    {
        previous = current;
        current = current->next;
        delete previous;
    }
}

// 判断给定下标是否越界
template <typename T>
inline bool List<T>::OutOfBound(unsigned int _index) const
{
    return _index > size;
}

// 返回链表的长度
template <typename T>
inline unsigned int List<T>::Length() const
{
    return size;
}

template <typename T>
Node<T>* List<T>::ForewardTrace(Node<T>* _entry, unsigned int _offset)
{
    Node<T>* current = _entry;
    for (int i = 0; i < _offset; i++)
    {
        current = current->next;
    }
    return current;
}

template <typename T>
Node<T>* List<T>::BackwardTrace(Node<T>* _entry, unsigned int _offset)
{
    Node<T>* current = _entry;
    for (int i = 0; i < _offset; i++)
    {
        current = current->last;
    }
    return current;
}

template <typename T>
Node<T>* List<T>::Trace(unsigned int _index)
{
    if (_index > size) { throw std::runtime_error("List::Trace(): Index out of bound."); }
    
    unsigned int footprintOffset = std::abs(static_cast<int>(footprintId) - static_cast<int>(_index));
    if (footprintOffset < std::min(size - _index + 1, _index))
    {
        footprintPtr = (footprintId < _index) ? ForewardTrace(footprintPtr, footprintOffset)
                                              : BackwardTrace(footprintPtr, footprintOffset);
    }
    else if (_index > (size >> 1))
    {
        footprintPtr = BackwardTrace(tail, size - _index + 1);
    }
    else
    {
        footprintPtr = ForewardTrace(head, _index);
    }
    footprintId = _index;
    
    return footprintPtr;
}

// 在给定的下标之后插入一个节点（会新建一个带值节点）
template <typename T>
void List<T>::InsertNode(T _tempValue, unsigned int _index)
{
    Node<T>* previous = Trace(_index);
    Node<T>* followed = previous->next;
    Node<T>* current = new Node<T> (_tempValue);
    current->last = previous;
    current->next = followed;
    previous->next = current;
    followed->last = current;
    size++;
    footprintId += static_cast<int>(_index < footprintId);
}

// 在给定的下标之后插入一个节点（通过重新链接来接入链表）【慎用】
// template <typename T>
// void List<T>::RewireNode(T* _NonTempValuePtr, unsigned int _index)
// {
//     Node<T>* previous = Trace(_index);
//     Node<T>* followed = previous->next;
//     Node<T>* current = new Node<T> (_NonTempValuePtr);
//     current->last = previous;
//     current->next = followed;
//     previous->next = current;
//     followed->last = current;
//     size++;
//     footprintId += static_cast<int>(_index < footprintId);
// }

// 在链表尾部追加一个节点（会新建一个带值节点）
template <typename T>
inline void List<T>::AppendNode(T _value)
{
    InsertNode(_value, size);
}

// 删除指定下标的节点
template <typename T>
void List<T>::DeleteNode(unsigned int _index)
{
    Node<T>* current = Trace(_index);
    Node<T>* previous = current->last;
    Node<T>* followed = current->next;
    previous->next = followed;
    followed->last = previous;
    delete current;
}

// 依据给定值查询是否存在该节点，若存在返回下标，否则返回 -1
template <typename T>
int List<T>::SeekNode(T _value)
{
    for (int i = 0; i < size; i++)
    {
        if (AccessNode(i) == _value)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
inline T& List<T>::AccessNode(unsigned int _index)
{
    return *(Trace(_index + 1)->value);
}

// 通过下标访问节点
template <typename T>
T& List<T>::operator[] (int _index)
{
    return AccessNode(_index);
}

class User;
class Course;
class Student;
class Teacher;

template class Node<User>;
template class Node<Course>;
template class Node<Student>;
template class Node<Teacher>;
