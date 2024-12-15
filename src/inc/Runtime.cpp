#include <Memory.hpp>
#include <cstdint>

using std::size_t;
using memory::CoreHeap;

void* __dso_handle = nullptr;

extern "C" int __cxa_atexit(void (*)(void*), void*, void*)
{
    return 0;
}

void* operator new(size_t count)
{
    return CoreHeap.Allocate(count);
}

void* operator new[](size_t count)
{
    return CoreHeap.Allocate(count);
}

void operator delete(void* ptr)
{
    CoreHeap.Release(ptr);
}

void operator delete[](void* ptr)
{
    CoreHeap.Release(ptr);
}
