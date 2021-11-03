#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

extern void* startDescriptor;

int meminit(void *pMemory, int size);

void memdone(void);

void *memalloc(int size);

void memfree(void *p);

int memgetminimumsize(void);

int memgetblocksize(void);

int* blockSizeInTheEnd(void* desc);

int* blockSize(void* desc);

void** blockPtr(void* desc);


#ifdef __cplusplus
}
#endif

#endif
