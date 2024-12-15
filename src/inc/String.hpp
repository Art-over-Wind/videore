#pragma once
#include <cstdint>
#include <Memory.hpp>

#include "Iterator.hpp"

using memory::CoreHeap;
using memory::Copy;

namespace type
{
    /**
     * A dynamic-length string.
     */
    class String : public Iterable<char>
    {
        /// Pointer to the raw string allocated in heap.
        char* str;

        /// String length including the null terminator.
        uint32_t length;

        /// Index used to iterate through the string.
        uint32_t index;

    public:

        /**
         * @brief Create a new string from the raw char sequence.
         * @param data Raw null-terminated data string.
         */
        String(const char* data)
            : length(GetLen(data))
        {
            str = static_cast<char*>(CoreHeap.Allocate(length));
            Copy(str, data, length);
        }

        /**
         * @brief Release the allocated string.
         */
        ~String()
        {
            CoreHeap.Release(str);
        }

        char operator[](uint32_t idx) const
        {
            return str[idx];
        }

        Iterator<char> begin() const override
        {
            return Iterator<char>(str);
        }

        /**
         * @brief Return iterator to the last character (It is always a null terminator).
         * @return Iterator to the null symbol.
         */
        Iterator<char> end() const override
        {
            return Iterator<char>(str + length - 1);
        }

        /**
         * @brief Get the null-terminated string's length.
         * @param str A null-terminated string.
         * @return Length, including the null terminator.
         */
        static uint32_t GetLen(const char* str)
        {
            uint32_t len = 0;
            while (*str++) len++;

            // Add a byte for the null terminator first.
            return len+1;
        }

        /**
         * @brief Return a pointer to the string.
         * @return Pointer to the raw null-terminated char sequence.
         */
        char* Chars() const
        {
            return str;
        }

        /**
         * @brief Get length of the string.
         * @return String length.
         */
        uint32_t Length() const
        {
            return length;
        }
    };
}
