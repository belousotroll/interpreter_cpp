#pragma once

template<typename T>
struct Node;

template<typename T>
struct List
{
    using value_type = T;

    Node<T> *   top  = nullptr;
    std::size_t size = 0;
};
