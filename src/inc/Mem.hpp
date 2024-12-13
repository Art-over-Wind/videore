#pragma once
#include <stdint.h>
#define MMIO_BASE 0x7E000000
#define MEM_PAGE_SIZE 4096
/**
 * @brief Start of the memory allowed to use.
 *
 * @details Memory before that address is mapped onto MMIO, cache, this bootcode, etc.
 */
#define MEM_USABLE 0x80000000

/**
 * Start of the kernel heap.
 */
#define MEM_KERNEL_HEAP ((void*)MEM_USABLE)
#define MEM_HEAP_ALIGN 4
#define MEM_HEAP_SIZE 64

/**
 * @brief Align @code addr @endcode by a given @code alignment @endcode.
 *
 * @note @code alignment @endcode must be power of 2.
 */
#define MEM_ALIGN(addr, alignment) ((addr + alignment - 1) & ~(alignment - 1))

/**
* Memory management.
*/
namespace mem
{
    /**
     * @brief A heap implementation.
     */
    class Heap
    {
        /**
         * A heap block header.
         */
        struct Node
        {
            /**
             * Pointer to the next node.
             *
             * Equals to @code NULL @endcode if there is no next node.
             */
            Node* next;

            /**
             * Data block size (@b excluding the node header).
             */
            uint32_t size;

            /**
             * Is the node in use already?
             */
            bool used;

            /**
             * Actual data.
             */
            char data[];

            /**
             * Create a null node.
             */
            Node()
            {
                next = nullptr;
                size = 0;
                used = true;
            }
        };

        /**
         * Pointer to the first node in the chain.
         */
        Node* root;

        /**
         * Pointer to the end of the heap.
         */
        void* end;

    public:
        /**
         * @brief init a new heap in the specified @p base address.
         *
         * @details Basically, only creates a null node at the given address.
         *
         * @param[in] base Base address of the heap.
         * @param[in] size Size of the heap in 4KB pages.
         */
        Heap(void* base, uint32_t size)
        {
            root = (Node*)base;
            *root = Node();

            end = (char*)base + (MEM_PAGE_SIZE * size);
        }

        ~Heap()
        {
            root->used = false;
        }

        /**
         * @brief Allocate some bytes to the heap
         * and return pointer to the data chunk.
         *
         * @param[in] size Requested size of the block in bytes.
         * @returns Pointer to the data chunk.
         * @returns @code nullptr @endcode if not enough
         * dedicated to the heap memory left.
         */
        void* Allocate(uint32_t size);

        /**
         * @brief Free the memory allocated by the @code Allocate @endcode method.
         *
         * @param[in] ptr Pointer to the memory chunk.
         */
        static void Free(void* ptr);
    };

    /// Main kernel heap.
    static Heap KernelHeap = Heap(MEM_KERNEL_HEAP, MEM_HEAP_SIZE);
}