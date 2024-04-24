#include <cassert>
#include <cstring>

#include "BlockAllocator.h"

#ifndef _ALLOCATOR_ALIGN

#define _ALLOCATOR_ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))

#endif //!_ALLOCATOR_ALIGN

using namespace slimenano::memory;

Allocator::Allocator()
    : m_szDataSize(0), m_szPageSize(0), m_szAlignmentSize(0), m_szBlockSize(0), m_nBlocksPrePage(0),
      m_nPages(0), m_nBlocks(0), m_nFreeBlocks(0), m_pPageList(nullptr), m_pFreeList(nullptr)
{
}

Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment)
    : m_szDataSize(0), m_szPageSize(0), m_szAlignmentSize(0), m_szBlockSize(0), m_nBlocksPrePage(0),
      m_nPages(0), m_nBlocks(0), m_nFreeBlocks(0), m_pPageList(nullptr), m_pFreeList(nullptr)
{
    Reset(data_size, page_size, alignment);
}

Allocator::~Allocator()
{
    FreeAll();
}

void Allocator::Reset(size_t data_size, size_t page_size, size_t alignment)
{
    FreeAll();

    m_szDataSize = data_size;
    m_szPageSize = page_size;

    size_t minimal_size = (sizeof(BlockHeader) > m_szDataSize) ? sizeof(BlockHeader) : m_szDataSize;

// assert the alignment must is 2^n
#ifdef _DEBUG

    assert(alignment > 0 && ((alignment & (alignment - 1))) == 0);

#endif //!_DEBUG

    m_szBlockSize = _ALLOCATOR_ALIGN(minimal_size, alignment);

    m_szAlignmentSize = m_szBlockSize - minimal_size;

    m_nBlocksPrePage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
}

void *Allocator::Allocate()
{
    if (!m_pFreeList)
    {
        // allocate new page
        PageHeader *pNewPage = reinterpret_cast<PageHeader *>(new uint8_t[m_szPageSize]);
        ++m_nPages;
        m_nBlocks += m_nBlocksPrePage;
        m_nFreeBlocks += m_nBlocksPrePage;

#ifdef _DEBUG
        FillFreePage(pNewPage);
#endif

        if (m_pPageList)
        {
            pNewPage->pNext = m_pPageList;
        }

        m_pPageList = pNewPage;

        BlockHeader *pBlock = pNewPage->Blocks();

        for (uint32_t i = 0; i < m_nBlocksPrePage; i++)
        {
            pBlock->pNext = NextBlock(pBlock);
            pBlock = NextBlock(pBlock);
        }
        pBlock->pNext = nullptr;

        m_pFreeList = pNewPage->Blocks();
    }

    BlockHeader *freeBlock = m_pFreeList;
    m_pFreeList = m_pFreeList->pNext;
    --m_nFreeBlocks;

#ifdef _DEBUG

    FillAllocatedBlock(freeBlock);

#endif

    return reinterpret_cast<void *>(freeBlock);
}

void Allocator::Free(void *p)
{

    BlockHeader *block = reinterpret_cast<BlockHeader *>(p);

#ifdef _DEBUG

    FillFreeBlock(block);

#endif

    block->pNext = m_pFreeList;
    m_pFreeList = block;
    ++m_nFreeBlocks;
}

void Allocator::FreeAll()
{

    PageHeader *pPage = m_pPageList;
    while (pPage)
    {

        PageHeader *_p = pPage;
        pPage = pPage->pNext;

        delete[] reinterpret_cast<uint8_t *>(_p);
    }

    m_pPageList = nullptr;
    m_pFreeList = nullptr;

    m_nPages = 0;
    m_nBlocks = 0;
    m_nFreeBlocks = 0;
}

BlockHeader *Allocator::NextBlock(BlockHeader *pBlock)
{
    return reinterpret_cast<BlockHeader *>(reinterpret_cast<uint8_t *>(pBlock) + m_szBlockSize);
}

#ifdef _DEBUG

void Allocator::FillFreePage(PageHeader *pPage)
{

    pPage->pNext = nullptr;

    BlockHeader *pBlock = pPage->Blocks();
    for (uint32_t i = 0; i < m_nBlocksPrePage; i++)
    {
        FillFreeBlock(pBlock);
        pBlock = NextBlock(pBlock);
    }
}

void Allocator::FillFreeBlock(BlockHeader *pBlock)
{
    std::memset(pBlock,
                PATTERN_FREE,
                m_szBlockSize - m_szAlignmentSize);

    std::memset(reinterpret_cast<uint8_t *>(pBlock) + m_szBlockSize - m_szAlignmentSize,
                PATTERN_ALIGN,
                m_szAlignmentSize);
}

void Allocator::FillAllocatedBlock(BlockHeader *pBlock)
{
    std::memset(pBlock,
                PATTERN_ALLOC,
                m_szBlockSize - m_szAlignmentSize);

    std::memset(reinterpret_cast<uint8_t *>(pBlock) + m_szBlockSize - m_szAlignmentSize,
                PATTERN_ALIGN,
                m_szAlignmentSize);
}

#endif