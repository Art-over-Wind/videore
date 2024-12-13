#include <Mem.hpp>

namespace mem
{
    void* Heap::Allocate(uint32_t size)
    {
        size = MEM_ALIGN(size, MEM_HEAP_ALIGN);

        // Speculative end address of this block (if it's created as new one).
        uint64_t spec_end;

        // Pointer to the new block.
        Node* new_ptr;
        Node* node = this->root;

        // Seek for free blocks.
        while (node->next)
        {
            node = node->next;

            // If free block is large enough to keep all requested data.
            if (!node->used && node->size >= size)
            {
                node->used = true;
                return node->data;
            }
        }

        // If all blocks are used or freed ones are not large enough, create a new one.
        spec_end = (uint64_t)node->data
            + node->size
            + size
            + sizeof(Node);

        // If there is not enough free memory to store the block.
        if (spec_end >= (uint64_t)end)
        {
            return nullptr;
        }

        new_ptr = (Node*)(spec_end - sizeof(Node) - size);
        new_ptr->used = true;
        new_ptr->size = size;

        return new_ptr->data;
    }

    void Heap::Free(void* data)
    {
        Node* node = (Node*)((uint64_t)data - sizeof(Node));
        node->used = false;
    }
}