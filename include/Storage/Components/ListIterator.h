#pragma once

#include <cstdint>

template<typename T>
struct Node;

template<typename T>
struct List;

template<typename T>
class ListIterator
{
    std::size_t position;
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    explicit ListIterator(Node<T> * node, std::size_t position)
        : m_node(node)
        , position{position}
    {}

    ListIterator& operator++()
    {
        m_node = m_node->next;
        ++position;
        return *this;
    }

    bool operator!=(const ListIterator& other) const
    {
        return position != other.position;
    }

    T& operator*() const
    {
        return m_node->value;
    }

private:
    Node<T> * m_node;
};

template<typename T>
ListIterator<T> begin(const List<T> & storage)
{
    return ListIterator{storage.top, 0};
}

template<typename T>
ListIterator<T> end(const List<T> & storage)
{
    // truck train plane
    const auto size = storage.size;
    Node<T> * node = storage.top;

    for (auto i = std::size_t{1}; i < size; ++i)
    {
        node = node->next;
    }

    return ListIterator{node, size};
}