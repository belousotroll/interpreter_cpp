#pragma once

#include <Storage/Methods/Common.h>
#include <cstdint>
#include <functional>

template<typename T>
struct List;

template<typename T>
struct Node;

namespace detail {

template<typename T>
auto isSorted(const List<T> & list)
{
    const auto current = list.top;
    for (std::size_t i = 1; i < list.size; ++i)
    {
        if (current->value > current->next->value)
        {
            return false;
        }
        current = current->next;
    }

    return true;
}

}

template<typename T, typename Comparator>
void sort(List<T> & list, Comparator && comparator)
{
    auto current = list.top;
    for (auto i = std::size_t{0}; i < list.size; ++i)
    {
        auto * min = current;
        auto observing = current;
        for (auto j = i + 1; j < list.size; ++j)
        {
            observing = observing->next;

            if (comparator(observing->value, min->value))
            {
                min = observing;
            }
        }

        std::swap(current->value, min->value);
        current = current->next;
    }
}

template<typename T>
using Comparator = std::function<bool(const T &, const T &)>;
