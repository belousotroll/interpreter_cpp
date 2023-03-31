#pragma once

#include <Storage/Methods/Common.h>

#include <memory>

template<typename T>
struct List;

template<typename T>
struct Node;

namespace detail {

    template<typename T, typename R>
    void toEmptyList(List<T> & storage, R && value)
    {
        auto node = new Node<T>(std::forward<R>(value));
        node->next = node;
        node->prev = node;

        storage.top = node;
        ++storage.size;
    }

    template<typename T, typename R>
    void toNonEmptyList(List<T> & storage, R && value)
    {
        auto node = new Node<T>(std::forward<R>(value));

        auto * top = storage.top;

        auto * last = top;
        for (auto i = size_t{1}; i < size(storage); ++i)
        {
            last = last->next;
        }

        node->next = top;
        top->prev = node;

        last->next = node;
        node->prev = last;

        ++storage.size;
    }
}

template<typename T>
void add(List<T> & storage, T && value)
{
    (detail::isEmpty(storage))
        ? detail::toEmptyList(storage, std::forward<T>(value))
        : detail::toNonEmptyList(storage, std::forward<T>(value));
}

template<typename T, typename R>
void add(List<T> & storage, R && value)
{
    const auto t = detail::isEmpty(storage);
    (detail::isEmpty(storage))
        ? detail::toEmptyList(storage, std::forward<R>(value))
        : detail::toNonEmptyList(storage, std::forward<R>(value));
}



