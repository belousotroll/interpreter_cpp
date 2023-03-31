#pragma once

namespace detail {

template<typename Storage, typename T = Storage::value_type>
auto size(const Storage & storage)
{
    return storage.size;
}

template<typename Storage, typename T = Storage::value_type>
auto isEmpty(const Storage & storage)
{
    return static_cast<bool>(size(storage) == 0);
}

template<typename T>
void swap(Node<T> * left, Node<T> * right)
{
    if (left && right)
    {
        std::swap(left->value, right->value);
    }
}

}