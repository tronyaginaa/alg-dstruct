#include <stdio.h>
#include <stdlib.h>
#include "memallocator.h"

void* startPoint = NULL;
void* endPoint = NULL;
int memSize = 0;
void* startDescriptor = NULL;
void* actualDescriptor = NULL;

int* blockSize(void* descriptor) {
    return (int*)descriptor;
}

void** blockPtr(void* descriptor) {
    return (void**)((char*)descriptor + sizeof(int));
}

int* blockSizeInTheEnd(void* descriptor) {
    return (int*)((char*)descriptor + abs(*blockSize(descriptor)) - sizeof(int));
}

void* prevBlock(void* descriptor) {
    return (void*)((char*)descriptor - abs(*((int*)descriptor - 1)));
}

void* nextBlock(void* descriptor) {
    return (void*)((char*)descriptor + *blockSize(descriptor));
}

int memgetminimumsize() {
    return 2 * sizeof(int) + sizeof(void*);
}

int memgetblocksize() {
    return 2 * sizeof(int) + sizeof(void*);
}

int meminit(void* pMemory, int size) {
    if (!pMemory || (size <= memgetminimumsize()))
        return 0;
    void* descriptor = pMemory;
    *blockSize(descriptor) = size;
    *blockPtr(descriptor) = NULL;
    *blockSizeInTheEnd(descriptor) = size;
    startDescriptor = descriptor;
    actualDescriptor = startDescriptor;
    startPoint = pMemory;
    endPoint = (char*)startPoint + size;
    memSize = size;

    return memSize;
}

void* memalloc(int size) {
    if (size < 1 || size > memSize - memgetblocksize())
        return NULL;
    size += memgetblocksize();
    void *usedDescriptor = actualDescriptor, *prevDescriptor = NULL;
    void *allocMemory = NULL;
    while (usedDescriptor) {
        if (*blockSize(usedDescriptor) >= size) {
            allocMemory = (void*)((char*)usedDescriptor + sizeof(int) + sizeof(void*));
            break;
        }
        prevDescriptor = usedDescriptor;
        usedDescriptor = *blockPtr(usedDescriptor);
        if (actualDescriptor != startDescriptor && usedDescriptor == NULL) 
            usedDescriptor = startDescriptor;
        if (usedDescriptor == actualDescriptor) {
            break;
        }
    }
    if (!allocMemory) 
        return NULL;
    if (*blockSize(usedDescriptor) > size + memgetblocksize()) {
        void *newDescriptor = (void*)((char*)usedDescriptor + size);
        *blockSize(newDescriptor) = *blockSize(usedDescriptor) - size;
        *blockPtr(newDescriptor) = *blockPtr(usedDescriptor);
        *blockSizeInTheEnd(newDescriptor) = *blockSize(newDescriptor);
        if (usedDescriptor == startDescriptor)
            startDescriptor = newDescriptor;
        else
            *blockPtr(prevDescriptor) = newDescriptor;
        *blockSize(usedDescriptor) = size;
    }
    else {
        if (prevDescriptor == NULL)
            startDescriptor = *blockPtr(usedDescriptor);
        else 
             *blockPtr(prevDescriptor) = *blockPtr(usedDescriptor);
    }
    if (*blockPtr(usedDescriptor) != NULL)
        actualDescriptor = *blockPtr(usedDescriptor);
    else
        actualDescriptor = startDescriptor;
    *blockSize(usedDescriptor) *= -1;
    *blockSizeInTheEnd(usedDescriptor) = *blockSize(usedDescriptor);
    *blockPtr(usedDescriptor) = NULL;

    return allocMemory;
}

void memfree(void* p) {
    void *prevDescriptor = NULL, *usedDescriptor = NULL, *nextDescriptor = NULL;
    usedDescriptor = (void*)((char*)p - sizeof(void*) - sizeof(int));
    *blockSize(usedDescriptor) *= -1;
    *blockSizeInTheEnd(usedDescriptor) = *blockSize(usedDescriptor);
    nextDescriptor = nextBlock(usedDescriptor);
    if ((char*)usedDescriptor - (char*)startPoint > memgetblocksize()) 
        prevDescriptor = prevBlock(usedDescriptor);
    int prevMerge = 0, nextMerge = 0;
    if (prevDescriptor >= startPoint && *blockSize(prevDescriptor) > 0) {
        prevMerge = 1;
        *blockSize(prevDescriptor) += *blockSize(usedDescriptor);
        *blockSizeInTheEnd(prevDescriptor) = *blockSize(prevDescriptor);
        usedDescriptor = prevDescriptor;
    }
    if ((char*)nextDescriptor < (char*)endPoint && *blockSize(nextDescriptor) > 0) {
        if (prevMerge == 0) {
            *blockPtr(usedDescriptor) = startDescriptor;
            startDescriptor = usedDescriptor;
        }
        void* nextBlockPrev = startDescriptor;
        void* tmp = startDescriptor;
        while (tmp) {
            if (*blockPtr(tmp) == nextDescriptor) {
                nextBlockPrev = tmp;
                break;
            }
            tmp = *blockPtr(tmp);
        }
        if (nextBlockPrev != nextDescriptor)
            *blockPtr(nextBlockPrev) = *blockPtr(nextDescriptor);
        else
            startDescriptor = *blockPtr(nextDescriptor);
        *blockSize(usedDescriptor) += *blockSize(nextDescriptor);
        *blockSizeInTheEnd(usedDescriptor) = *blockSize(usedDescriptor);
        if (actualDescriptor == nextDescriptor)
            actualDescriptor = usedDescriptor;
        nextMerge = 1;
    }
    if (prevMerge == 0 && nextMerge == 0) {
        *blockPtr(usedDescriptor) = startDescriptor;
        startDescriptor = usedDescriptor;
        actualDescriptor = usedDescriptor;
    }
}

void memdone() {
    void *ptr = startPoint;
    while (ptr < endPoint) {
        if (*blockSize(ptr) < 0)
            fprintf(stderr, "Memory leaks! Block: 0x%p\n", (char*)ptr + sizeof(int) + sizeof(void*));
        ptr = (void*)((char*)ptr + abs(*blockSize(ptr)));
    }
}
