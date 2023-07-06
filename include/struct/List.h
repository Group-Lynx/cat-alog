#ifndef LIST_H
#define LIST_H

#include "../struct/Node.h"
#include "../utility/LynType.h"

#include <optional>
#include <stdexcept>
#include <memory>

// == 声明 == //

template <typename T>
class List
{
    friend class Node<T>;

private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    Index_t size;
    std::shared_ptr<Node<T>> footprintPtr;
    Index_t footprintIdx;

public:
    List();
    ~List();

public:
    bool OutOfRange(Index_t _index) const noexcept;
    Index_t Length() const noexcept;

private:
    std::shared_ptr<Node<T>> ForewardTrace(std::shared_ptr<Node<T>> _entry, Index_t _offset) noexcept;
    std::shared_ptr<Node<T>> BackwardTrace(std::shared_ptr<Node<T>> _entry, Index_t _offset) noexcept;
    std::shared_ptr<Node<T>> Trace(Index_t _index);

public:
    void Clear();
    bool Insert(T _value, Index_t _index);
    void Append(T _value);
    bool Delete(Index_t _index);
    template <typename Key_t> bool Remove(Key_t _key);

public:
    template <typename Key_t> std::optional<T> Search(Key_t _key);
    template <typename Key_t> std::optional<Index_t> Trieve(Key_t _key);

private:
    T& Access(Index_t _index);

public:
    T& operator[](Index_t _index);
};

// == 定义 == //

// 构建一个空的双向链表。
template <typename T>
List<T>::List()
{
    head = std::make_shared<Node<T>>();
    tail = std::make_shared<Node<T>>();
    head->next = tail;
    tail->last = head;
    size = 0;
    footprintPtr = head;
    footprintIdx = 0;
}

template <typename T>
List<T>::~List() = default;

// 检查给定下标是否越界。
template <typename T>
inline bool List<T>::OutOfRange(Index_t _index) const noexcept
{
    return _index > size;
}

// 获取链表的长度。
template <typename T>
inline Index_t List<T>::Length() const noexcept
{
    return size;
}

// 【注意】该函数由 Trace() 托管，不应被直接调用。
// 正向追溯获取节点。
template <typename T>
std::shared_ptr<Node<T>> List<T>::ForewardTrace(std::shared_ptr<Node<T>> _entry, Index_t _offset) noexcept
{
    std::shared_ptr<Node<T>> current = _entry;
    for (Index_t i = 0; i < _offset; i++)
    {
        current = current->next;
    }
    return current;
}

// 【注意】该函数由 Trace() 托管，不应被直接调用。
// 逆向追溯获取节点。
template <typename T>
std::shared_ptr<Node<T>> List<T>::BackwardTrace(std::shared_ptr<Node<T>> _entry, Index_t _offset) noexcept
{
    std::shared_ptr<Node<T>> current = _entry;
    for (Index_t i = 0; i < _offset; i++)
    {
        current = current->last;
    }
    return current;
}

// 依据给定下标追溯并获取节点。
template <typename T>
std::shared_ptr<Node<T>> List<T>::Trace(Index_t _index)
{
    if (OutOfRange(_index))
    {
        throw std::out_of_range("`Trace()`: index out of range.");
    }
    
    Index_t footprintOffset = std::abs(static_cast<int>(footprintIdx) - static_cast<int>(_index));
    if (footprintOffset < std::min(size - _index + 1, _index))
    {
        footprintPtr = (footprintIdx < _index) ? ForewardTrace(footprintPtr, footprintOffset)
                                               : BackwardTrace(footprintPtr, footprintOffset);
    }
    else if (_index > (size / 2))
    {
        footprintPtr = BackwardTrace(tail, size - _index + 1);
    }
    else
    {
        footprintPtr = ForewardTrace(head, _index);
    }
    footprintIdx = _index;
    
    return footprintPtr;
}

// 清空链表。
template <typename T>
void List<T>::Clear()
{
    while (head->next != tail)
    {
        std::shared_ptr<Node<T>> current = head->next;
        head->next = current->next;
        current->next->last = head;
    }
    
    size = 0;
    footprintPtr = head;
    footprintIdx = 0;
}

// 在指定下标处插入一个元素。
template <typename T>
bool List<T>::Insert(T _value, Index_t _index)
{
    std::shared_ptr<Node<T>> previous = nullptr;
    
    try
    {
        previous = Trace(_index);
    }
    catch(const std::out_of_range& e)
    {
        return false;
    }
    
    std::shared_ptr<Node<T>> followed = previous->next;
    std::shared_ptr<Node<T>> current = std::make_shared<Node<T>>(_value);
    current->last = previous;
    current->next = followed;
    previous->next = current;
    followed->last = current;
    size++;
    footprintIdx += static_cast<int>(_index < footprintIdx);
    
    return true;
}

// 在链表尾部追加一个元素。
template <typename T>
void List<T>::Append(T _value)
{
    Insert(_value, size);
}

// 依据给定下标，在链表中删除一个元素。
template <typename T>
bool List<T>::Delete(Index_t _index)
{
    std::shared_ptr<Node<T>> current = nullptr;
    
    try
    {
        current = Trace(_index);
    }
    catch(const std::out_of_range& e)
    {
        return false;
    }
    
    std::shared_ptr<Node<T>> previous = current->last;
    std::shared_ptr<Node<T>> followed = current->next;
    previous->next = followed;
    followed->last = previous;
    size--;
    
    footprintPtr = previous;
    footprintIdx -= static_cast<int>(_index < footprintIdx);
    
    return true;
}

// 依据给定键值，在链表中删除一个元素。
template <typename T>
template <typename Key_t>
bool List<T>::Remove(Key_t _key)
{
    std::optional<Index_t> result = Trieve(_key);
    
    if (!result.has_value())
    {
        return false;
    }
    
    std::shared_ptr<Node<T>> current = Trace(result.value() + 1);
    std::shared_ptr<Node<T>> previous = current->last;
    std::shared_ptr<Node<T>> followed = current->next;
    previous->next = followed;
    followed->last = previous;
    size--;
    
    footprintPtr = previous;
    footprintIdx -= static_cast<int>(result.value() < footprintIdx);
    
    return true;
}

// 使用给定的键值在链表中查询元素，并获取其值。
template <typename T>
template <typename Key_t>
std::optional<T> List<T>::Search(Key_t _key)
{
    std::shared_ptr<Node<T>> current = head->next;
    
    while (current != tail)
    {
        if (*(current->value) == _key)
        {
            return *(current->value);
        }
        current = current->next;
    }
    
    return std::nullopt;
}

// 使用给定的键值在链表中查询元素，并获取其下标。
template <typename T>
template <typename Key_t>
std::optional<Index_t> List<T>::Trieve(Key_t _key)
{
    std::shared_ptr<Node<T>> current = head->next;
    
    for (int i = 0; current != tail; i++)
    {
        if (*(current->value) == _key)
        {
            return i;
        }
        current = current->next;
    }
    
    return std::nullopt;
}

// 以下标为凭据访问一个元素。
template <typename T>
inline T& List<T>::Access(Index_t _index)
{
    return *(Trace(_index + 1)->value);
}

// 以下标为凭据访问一个元素。
template <typename T>
T& List<T>::operator[](Index_t _index)
{
    return Access(_index);
}

#endif