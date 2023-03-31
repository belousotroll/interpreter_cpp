#pragma once

#include <Storage/Methods/Common.h>

#include <vector>
#include <functional>

template<typename T>
struct List;

template<typename T>
struct Node;

namespace detail {

    template<typename T, typename Comparator>
    auto findMatches(const List<T> storage, Comparator && comparator)
    {
        auto collection = std::vector<Node<T>*>{};

        auto iter = storage.top;
        for (auto i = std::size_t{0}; i < storage.size; ++i)
        {
            if (comparator(iter->value))
            {
                collection.emplace_back(iter);
            }

            iter = iter->next;
        }

        return collection;
    }

    template<typename T, typename Collection>
    void removeElements(List<T> & storage, const Collection & collection)
    {
        if (detail::isEmpty(storage))
        {
            return;
        }

        for (auto * val : collection)
        {
            auto & prev = val->prev;
            auto & next = val->next;

            prev->next = val->next;
            next->prev = val->prev;

            --storage.size;

            if (storage.top == val)
            {
                storage.top = val->next;
            }
            else if (detail::isEmpty(storage))
            {
                storage.top  = nullptr;
            }

            delete val;
        }

    }
}

template<typename T, typename Comparator>
void remove_if(List<T> & storage, Comparator && comparator)
{
    if (detail::isEmpty(storage))
    {
        return;
    }

    if (auto matches = detail::findMatches(storage, std::forward<Comparator>(comparator)); !matches.empty())
    {
        detail::removeElements(storage, matches);
    }
}

template<typename T>
using Predicat = std::function<bool(const T &)>;