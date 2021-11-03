#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <stdlib.h>
#include <string.h>
#include "memallocator.h"


#define TEST_SIZE 20

TEST(memgetminimumsize_Test, memgetminimumsizeMatch)
{
    int a = memgetminimumsize();
    EXPECT_EQ(a, 12);
}

TEST(memgetblocksize_Test, memgetblocksizeMatch)
{
    int a = memgetminimumsize();
    EXPECT_EQ(a, 12);
}

TEST(meminit_Test, InitializedDataMatch) {
    const int MEMORY_SIZE = memgetminimumsize() + 1;
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void* desc = ptr;
    EXPECT_EQ(bytes, MEMORY_SIZE);
    EXPECT_EQ(*blockSize(desc), MEMORY_SIZE);
    EXPECT_EQ(*blockPtr(desc), nullptr);
    EXPECT_EQ(*blockSizeInTheEnd(desc), MEMORY_SIZE);
    free(ptr);
}

TEST(meminit_Test, NotEnoughSizeToInit) {
    const int LITTLE_MEMORY_SIZE = memgetminimumsize();
    void* ptr = malloc(LITTLE_MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, LITTLE_MEMORY_SIZE);
    EXPECT_EQ(bytes, 0);
    free(ptr);
}

TEST(memalloc_Test, AllMemoryForOneBlock) {
    const int MEMORY_SIZE = memgetminimumsize() + TEST_SIZE;
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void* desc = ptr;
    void* mem = memalloc(TEST_SIZE);
    EXPECT_EQ(bytes, MEMORY_SIZE);
    EXPECT_EQ(*blockSize(desc), -MEMORY_SIZE);
    EXPECT_EQ(*blockPtr(desc), nullptr);
    EXPECT_EQ(*blockSizeInTheEnd(desc), -MEMORY_SIZE);
    free(ptr);
}

TEST(memalloc_Test, NoEmptyptyBlock) {
    const int MEMORY_SIZE = memgetminimumsize() + TEST_SIZE;
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void* desc = ptr;
    void* mem1 = memalloc(TEST_SIZE);
    void* mem2 = memalloc(TEST_SIZE);
    EXPECT_EQ(mem2, nullptr);
    EXPECT_EQ(bytes, MEMORY_SIZE);
    EXPECT_EQ(*blockSize(desc), -MEMORY_SIZE);
    EXPECT_EQ(*blockPtr(desc), nullptr);
    EXPECT_EQ(*blockSizeInTheEnd(desc), -MEMORY_SIZE);
    free(ptr);
}

TEST(memfree_Test, FreeOneBlock) {
    const int MEMORY_SIZE = memgetminimumsize() + sizeof(char);
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void* allInitMemory = ptr;
    *blockSize(allInitMemory) = -*blockSize(allInitMemory);
    *blockPtr(allInitMemory) = nullptr;
    *blockSizeInTheEnd(allInitMemory) = *blockSize(allInitMemory);
    startDescriptor = nullptr;
    void* user_ptr_to_block = (void*)((char*)allInitMemory + sizeof(int) + sizeof(void*));
    memfree(user_ptr_to_block);
    EXPECT_EQ(*blockSize(allInitMemory), abs(*blockSize(allInitMemory)));
    EXPECT_EQ(*blockSizeInTheEnd(allInitMemory), abs(*blockSizeInTheEnd(allInitMemory)));
    EXPECT_EQ(startDescriptor, ptr);
    free(ptr);
}

TEST(memfree_Test, FreeBlockWFreeRightBlock) {
    const int MEMORY_SIZE = memgetminimumsize() + memgetblocksize() + 2 * sizeof(char);
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void* allocatedBlock = ptr;
    *blockSize(allocatedBlock) = -((int)sizeof(char) + memgetblocksize()); // block is allocated so size is negative
    *blockPtr(allocatedBlock) = nullptr;
    *blockSizeInTheEnd(allocatedBlock) = *blockSize(allocatedBlock);
    void* freeBlock = (void*)((char*)allocatedBlock + abs(*blockSize(allocatedBlock)));
    startDescriptor = freeBlock;
    *blockSize(freeBlock) = (int)sizeof(char) + memgetblocksize();
    *blockPtr(freeBlock) = nullptr;
    *blockSizeInTheEnd(freeBlock) = *blockSize(freeBlock);
    void* ptrToAllocatedBlock = (void*)((char*)allocatedBlock + sizeof(int) + sizeof(void*));
    memfree(ptrToAllocatedBlock);
    EXPECT_EQ(*blockSize(allocatedBlock), bytes);
    EXPECT_EQ(*blockSizeInTheEnd(allocatedBlock), bytes);
    EXPECT_EQ(startDescriptor, ptr);
    free(ptr);
}

TEST(memfree_Test, FreeBlockWFreeLeftBlock) {
    const int MEMORY_SIZE = memgetminimumsize() + memgetblocksize() + 2 * sizeof(char);
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void* freeBlock = ptr;
    startDescriptor = freeBlock;
    *blockSize(freeBlock) = (int)sizeof(char) + memgetblocksize();
    *blockPtr(freeBlock) = nullptr;
    *blockSizeInTheEnd(freeBlock) = *blockSize(freeBlock);
    
    void* allocatedBlock = (void*)((char*)freeBlock + abs(*blockSize(freeBlock)));
    *blockSize(allocatedBlock) = -((int)sizeof(char) + memgetblocksize()); // block is allocated so size is negative
    *blockPtr(allocatedBlock) = nullptr;
    *blockSizeInTheEnd(allocatedBlock) = *blockSize(allocatedBlock);
    // now freeing and expect memory state similar with state after meminit
    void* ptrToAllocatedBlock = (void*)((char*)allocatedBlock + sizeof(int) + sizeof(void*));
    memfree(ptrToAllocatedBlock);
    EXPECT_EQ(*blockSize(freeBlock), bytes);
    EXPECT_EQ(*blockSizeInTheEnd(freeBlock), bytes);
    EXPECT_EQ(startDescriptor, ptr);
    free(ptr);
}

TEST(memfree_Test, FreeBlockBetweenTwoFreeBlocks) {
    const int MEMORY_SIZE = memgetminimumsize() + 2 * memgetblocksize() + 3 * sizeof(char);
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void* prevFreeBlock = ptr;
    startDescriptor = prevFreeBlock;
    *blockSize(prevFreeBlock) = (int)sizeof(char) + memgetblocksize();
    *blockPtr(prevFreeBlock) = nullptr;
    *blockSizeInTheEnd(prevFreeBlock) = *blockSize(prevFreeBlock);
    void* allocatedBlock = (void*)((char*)prevFreeBlock + abs(*blockSize(prevFreeBlock)));
    *blockSize(allocatedBlock) = -((int)sizeof(char) + memgetblocksize()); 
    *blockPtr(allocatedBlock) = nullptr;
    *blockSizeInTheEnd(allocatedBlock) = *blockSize(allocatedBlock);
    void* nextFreeBlock = (void*)((char*)allocatedBlock + abs(*blockSize(allocatedBlock)));
    *blockSize(nextFreeBlock) = (int)sizeof(char) + memgetblocksize();
    *blockPtr(nextFreeBlock) = nullptr;
    *blockSizeInTheEnd(nextFreeBlock) = *blockSize(nextFreeBlock);
    *blockPtr(prevFreeBlock) = nextFreeBlock;
    void* ptrToAllocatedBlock = (void*)((char*)allocatedBlock + sizeof(int) + sizeof(void*));
    memfree(ptrToAllocatedBlock);
    EXPECT_EQ(*blockSize(prevFreeBlock), bytes);
    EXPECT_EQ(*blockSizeInTheEnd(prevFreeBlock), bytes);
    EXPECT_EQ(*blockPtr(prevFreeBlock), nullptr);
    EXPECT_EQ(startDescriptor, ptr);
    free(ptr);
}

TEST(memalloc_FuncTest, ActualBlockSizeLessThanAsked) {
    const int MEMORY_SIZE = 3 * memgetblocksize() + 1 + 5 + 5;
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    char* mem1 = (char*)memalloc(5);
    char* mem2 = (char*)memalloc(5);
    char* mem3 = (char*)memalloc(1);
    EXPECT_TRUE(mem1);
    EXPECT_TRUE(mem2);
    EXPECT_TRUE(mem3);
    memfree(mem1);
    memfree(mem3);
    char* d = (char*)memalloc(5); 
    mem3 = (char*)memalloc(1);
    EXPECT_TRUE(d);
    EXPECT_TRUE(mem3);
    EXPECT_TRUE(d == mem1);
    memfree(d);
    memfree(mem2);
    memfree(mem3);
    memdone();
    free(ptr);
}


#define TEST_BLOCKS_COUNT 10000

TEST(memallocator_StressTest, ALotOfMemoryAllocAndFree) {
    const int TEST_BLOCK_SIZE = 16;
    const int TEST_MEMORY_SIZE = TEST_BLOCKS_COUNT * TEST_BLOCK_SIZE;
    const int MEMORY_SIZE = TEST_BLOCKS_COUNT * (TEST_BLOCK_SIZE + memgetblocksize());
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void** blocks = (void**)malloc(TEST_BLOCKS_COUNT * sizeof(void*));
    if (!blocks) {
        free(ptr);
        ASSERT_TRUE(blocks);
    }
    for (int i = 0; i < TEST_BLOCKS_COUNT; i++) {
        blocks[i] = (char*)memalloc(TEST_BLOCK_SIZE);
    }
    for (int i = 0; 2 * i < TEST_BLOCKS_COUNT; i++) {
        memfree(blocks[2 * i]);
    }
    for (int i = 0; 2 * i < TEST_BLOCKS_COUNT; i++) {
        blocks[2 * i] = (char*)memalloc(TEST_BLOCK_SIZE);
    }
    for (int i = 0; 2 * i + 1 < TEST_BLOCKS_COUNT; i++) {
        memfree(blocks[2 * i + 1]);
    }
    for (int i = 0; 2 * i < TEST_BLOCKS_COUNT; i++) {
        memfree(blocks[2 * i]);
    }
    EXPECT_EQ(*blockSize(ptr), bytes);
    EXPECT_EQ(*blockSizeInTheEnd(ptr), bytes);
    EXPECT_EQ(*blockPtr(ptr), nullptr);
    memdone();
    free(blocks);
    free(ptr);
}

TEST(memallocator_StressTest, RandomBlocksAllocAndFree) {
    const int TEST_BLOCK_SIZE = 16;
    const int TEST_MEMORY_SIZE = TEST_BLOCKS_COUNT * TEST_BLOCK_SIZE;
    const int MEMORY_SIZE = 2 * TEST_BLOCKS_COUNT * (TEST_BLOCK_SIZE + memgetblocksize()); 
    void* ptr = malloc(MEMORY_SIZE);
    ASSERT_TRUE(ptr);
    int bytes = meminit(ptr, MEMORY_SIZE);
    if (!bytes) {
        free(ptr);
        ASSERT_TRUE(bytes);
    }
    void** blocks = (void**)malloc(TEST_BLOCKS_COUNT * sizeof(void*));
    if (!blocks) {
        free(ptr);
        ASSERT_TRUE(blocks);
    }
    for (int i = 0; i < TEST_BLOCKS_COUNT; i++) {
        blocks[i] = (char*)memalloc(rand() % TEST_BLOCK_SIZE + 1);
    }
    for (int i = 0; 2 * i < TEST_BLOCKS_COUNT; i++) {
        memfree(blocks[2 * i]);
    }
    for (int i = 0; 2 * i < TEST_BLOCKS_COUNT; i++) {
        blocks[2 * i] = (char*)memalloc(TEST_BLOCK_SIZE);
    }
    for (int i = 0; 2 * i + 1 < TEST_BLOCKS_COUNT; i++) {
        memfree(blocks[2 * i + 1]);
    }
    for (int i = 0; 2 * i < TEST_BLOCKS_COUNT; i++) {
        memfree(blocks[2 * i]);
    }
    EXPECT_EQ(*blockSize(ptr), bytes);
    EXPECT_EQ(*blockSizeInTheEnd(ptr), bytes);
    EXPECT_EQ(*blockPtr(ptr), nullptr);
    memdone();
    free(blocks);
    free(ptr);
}