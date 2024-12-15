#include <cstdint>
#include <cstring>
#include <String.hpp>
#include <Memory.hpp>
#include <dev/crystall/Aux.hpp>

using memory::CoreHeap;
using memory::Copy;
using dev::crystall::aux::MiniUart;

namespace type
{
    String String::Add(const String& other) const
    {
        // New string length.
        // Subtract 1 byte - extra null terminator came from the second string.
        uint32_t new_len = length + other.length - 1;

        // Allocate space for the new string.
        String new_str = String(new_len);

        // Copy contents of the first string.
        // Exclude the null terminator.
        Copy(new_str.str, str, length - 1);

        // Copy content of the second string.
        Copy(
            new_str.str + length - 1,
            other.str,
            other.length);

        return new_str;
    }
}