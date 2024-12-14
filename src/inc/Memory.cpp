#include <Memory.hpp>

namespace memory
{
    void Copy(void* dst, const void* src, uint32_t size)
    {
        for (uint32_t i = 0; i < size; i++)
        {
            ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
        }
    }


    void* Heap::Allocate(uint64_t size)
    {
        size = MEM_ALIGN(size, MEM_HEAP_ALIGN);

        // Speculative end address of this block (if it's created as new one).
        uint64_t spec_end;

        // Pointer to the new block.
        Node* new_ptr;
        Node* node = this->root;

        // Seek for free nodes.
        while (node->next)
        {
            node = node->next;

            // If free block is large enough to keep all requested data.
            if (!node->used && node->size >= size)
            {
                uint64_t size_left = node->size - size;

                // If released node was larger than the new one
                // and if there are more than 0 available bytes,
                // create a new node on the left space.
                if (size_left >= sizeof(Node) && (size_left - sizeof(Node)) > 0)
                {
                    Node* new_node = (Node*)((uint64_t)node->data + size);
                    new_node->next = node->next;
                    new_node->prev = node;
                    node->next = new_node;
                    new_node->used = false;
                    new_node->size = size_left - sizeof(Node);
                    node->size = size;
                }
                // Else, just keep the node's size.

                node->used = true;
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
        new_ptr->next = nullptr;
        new_ptr->prev = node;
        new_ptr->size = size;

        return new_ptr->data;
    }

    void Heap::Release(void* ptr)
    {
        Node* node = HEADER_PTR(ptr);
        node->used = false;
    }
}