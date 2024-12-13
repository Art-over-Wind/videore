#pragma once
#include <cstdint>

namespace type
{
    class String
    {
        /// Pointer to the raw string.
        ///
        /// @todo Change it to vector type when it will be done.
        char* data;
    public:
        /**
         * @brief Create a new string from the given raw string.
         * @param raw Raw C string pointer.
         */
        String(char* raw) : data(raw) {}

        /**
         * @brief Find length of the given string.
         * @param[in] str Input string.
         * @return Length of the string (excluding@code \0@endcode).
         */
        static uint16_t Len(const char* str)
        {
            uint16_t length = 0;
            while (*str++) length++;
            return length;
        }

        /**
         * @brief Reverse character in the string.
         * @param buf A null-terminated string buffer.
         * @param length String length (including the null terminator).
         */
        static void Reverse(char* buf, uint16_t length);

        virtual String ToString() const;
    };
}
