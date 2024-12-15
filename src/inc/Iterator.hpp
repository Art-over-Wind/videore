#pragma once
#include <cstdint>

namespace type
{
    /**
     * @brief An array iterator.
     * @tparam T Type of each array member.
     */
    template <typename T>
    class Iterator
    {
        /// Pointer to the array.
        T* ptr;

    public:
        Iterator(T* ptr) : ptr(ptr) {}

        Iterator& operator++()
        {
            ++ptr;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator i = *this;
            ++*this;
            return i;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs.ptr == rhs.ptr;
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs.ptr != rhs.ptr;
        }

        T& operator*()
        {
            return *ptr;
        }
    };

    /**
     * @brief Trait for types that implement iterator.
     * @tparam T Type of each array member.
     */
    template <typename T>
    class Iterable
    {
    public:
        virtual Iterator<T> begin() const = 0;
        virtual Iterator<T> end() const = 0;
    };
}
