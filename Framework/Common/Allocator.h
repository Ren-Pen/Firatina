#pragma once
#ifndef __FRAMWORK_ALLOCATOR_H
#define __FRAMWORK_ALLOCATOR_H

#include <cstddef>
#include <cstdint>

namespace slimenano
{

    namespace memory
    {

        struct BlockHeader
        {
            BlockHeader *pNext;
        };

        struct PageHeader
        {
            PageHeader *pNext;
            BlockHeader *Blocks()
            {
                return reinterpret_cast<BlockHeader *>(this + 1);
            }
        };

        class Allocator
        {
        public:
            static const uint8_t PATTERN_ALIGN = 0xFC;
            static const uint8_t PATTERN_ALLOC = 0xFD;
            static const uint8_t PATTERN_FREE = 0xFE;

            Allocator(size_t data_size, size_t page_size, size_t alignment);
            ~Allocator();

            void Reset(size_t data_size, size_t page_size, size_t alignment);

            void *Allocate();
            void Free(void *p);
            void FreeAll();

        private:
#ifdef _DEBUG

            void FillFreePage(PageHeader *pPage);
            void FillFreeBlock(BlockHeader *pBlock);
            void FillAllocatedBlock(BlockHeader *pBlock);

#endif //!_DEBUG
            BlockHeader *NextBlock(BlockHeader *pBlock);

            PageHeader *m_pPageList;
            BlockHeader *m_pFreeList;

            size_t m_szDataSize;
            size_t m_szPageSize;
            size_t m_szAlignmentSize;
            size_t m_szBlockSize;
            uint32_t m_nBlocksPrePage;

            uint32_t m_nPages;
            uint32_t m_nBlocks;
            uint32_t m_nFreeBlocks;

            Allocator(const Allocator &clone) = delete;
            Allocator &operator=(const Allocator &rhs) = delete;
        };

    }

}

#endif // !__FRAMWORK_ALLOCATOR_H