#pragma once

#include <memory>

template<typename T>
struct Node
{
    explicit Node(T value)
        : value(value)
    {}

    T value;
    Node<T> * prev = nullptr;
    Node<T> * next = nullptr;
};