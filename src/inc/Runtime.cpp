#include <Mem.hpp>
#include <cstdint>

using std::size_t;
using mem::KernelHeap;

void* __dso_handle = nullptr;

extern "C" int __cxa_atexit(void (*)(void*), void*, void*)
{
    return 0;
}

void* operator new(size_t count)
{
    return KernelHeap.Allocate(count);
}

void* operator new[](size_t count)
{
    return KernelHeap.Allocate(count);
}

void operator delete(void* ptr)
{
    KernelHeap.Free(ptr);
}

void operator delete[](void* ptr)
{
    KernelHeap.Free(ptr);
}
