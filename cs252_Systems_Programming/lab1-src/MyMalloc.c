
//
// CS252: MyMalloc Project
//
// The current implementation gets memory from the OS
// every time memory is requested and never frees memory.
//
// You will implement the allocator as indicated in the handout.
// 
// Also you will need to add the necessary locking mechanisms to
// support multi-threaded programs.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>
#include "MyMalloc.h"

#define ALLOCATED 1
#define NOT_ALLOCATED 0
#define ARENA_SIZE 2097152

pthread_mutex_t mutex;

static bool verbose = false;

extern void atExitHandlerInC()
{
  if (verbose)
    print();
}

static void* getMemoryFromOS(size_t size)
{
  // Use sbrk() to get memory from OS
  _heapSize += size;
 
  void *mem = sbrk(size);

  if(!_initialized){
      _memStart = mem;
  }

  return mem;
}


/*
 * @brief retrieves a new 2MB chunk of memory from the OS
 * and adds "dummy" boundary tags
 * @param size of the request
 * @return a FreeObject pointer to the beginning of the chunk
 */
static FreeObject* getNewChunk(size_t size)
{
  void *mem = getMemoryFromOS(size);

  // establish fence posts
  BoundaryTag *fencePostHead = (BoundaryTag *)mem;
  setAllocated(fencePostHead, ALLOCATED);
  setSize(fencePostHead, 0);

  char *temp = (char *)mem + size - sizeof(BoundaryTag);
  BoundaryTag *fencePostFoot = (BoundaryTag *)temp;
  setAllocated(fencePostFoot, ALLOCATED);
  setSize(fencePostFoot, 0);
 
  return (FreeObject *)((char *)mem + sizeof(BoundaryTag));
}

/**
 * @brief If no blocks have been allocated, get more memory and 
 * set up the free list
 */
static void initialize()
{
  verbose = true;

  pthread_mutex_init(&mutex, NULL);

  // print statistics at exit
  atexit(atExitHandlerInC);

  FreeObject *firstChunk = getNewChunk(ARENA_SIZE);

  // initialize the list to point to the firstChunk
  _freeList = &_freeListSentinel;
  setSize(&firstChunk->boundary_tag, ARENA_SIZE - (2*sizeof(BoundaryTag))); // ~2MB
  firstChunk->boundary_tag._leftObjectSize = 0;
  setAllocated(&firstChunk->boundary_tag, NOT_ALLOCATED);

  // link list pointer hookups
  firstChunk->free_list_node._next = _freeList;
  firstChunk->free_list_node._prev = _freeList;
  _freeList->free_list_node._prev = firstChunk;
  _freeList->free_list_node._next = firstChunk;

  _initialized = 1;
}

/**
 * @brief TODO: PART 1
 * This function should perform allocation to the program appropriately,
 * giving pieces of memory that are large enough to satisfy the request. 
 * Currently, it just sbrk's memory every time.
 *
 * @param size size of the request
 *
 * @return pointer to the first usable byte in memory for the requesting
 * program
 */
static void* allocateObject(size_t size)
{
  //fprintf(stderr, "BLAH1 %d\n", count); 
  pthread_mutex_init(&mutex,NULL);
  // Make sure that allocator is initialized
  if (!_initialized)
    initialize();
  //Adjust size
  if(size == 0)
    return NULL;
  size_t roundedSize = ((size-1)/8 + 1)*8;
  size_t real_size = roundedSize + sizeof(BoundaryTag);
  if(real_size < sizeof(FreeObject))
	real_size = sizeof(FreeObject);
  //This If Block is pulled from Piazza #59, and
  //is functionally a part of the starter code.
  
  if(real_size > ARENA_SIZE - (3 * sizeof(BoundaryTag))){
    errno = ENOMEM;
    return NULL;
  }

  //Traverse Free List and find useable chunk
  int i = 0;
  do{
  //fprintf(stderr,"BLAH2\n");
  FreeObject * tempPtr;
  FreeObject * temp2Ptr;
  tempPtr = _freeList->free_list_node._next;
   while(tempPtr != _freeList){
    if(getSize(&tempPtr->boundary_tag) >= real_size){
      //Splitting if large enough
      if(getSize(&tempPtr->boundary_tag) >= real_size + sizeof(FreeObject)){	
	//Splitting
//	fprintf(stderr, "BLAH3 %d\n", real_size);	
        size_t size = getSize(&tempPtr->boundary_tag);
        temp2Ptr = (void *)tempPtr - sizeof(BoundaryTag) + size - real_size;
        setSize(&temp2Ptr->boundary_tag,real_size);
	size_t newSize = size - real_size;
	setSize(&tempPtr->boundary_tag, newSize);
        temp2Ptr->boundary_tag._leftObjectSize = size - real_size;
	BoundaryTag* nextObjTag = (void *)temp2Ptr + real_size;
	nextObjTag->_leftObjectSize = real_size;
	setAllocated(&temp2Ptr->boundary_tag, ALLOCATED);
//	fprintf(stderr, "BLAH3.5 %d\n", getSize(&temp2Ptr->boundary_tag));
//        fprintf(stderr, "isAllocated=%d\n", isAllocated(&temp2Ptr->boundary_tag));
	count++;
	return (void *)temp2Ptr + sizeof(BoundaryTag);
      }
      //fprintf(stderr, "BLAH5\n");
      //Set Allocated Bit
      setAllocated(&tempPtr->boundary_tag, ALLOCATED);
      //Remove from free list
      //fprintf(stderr, "BLAH6 realsize:%d %d %d \n", real_size, getSize(&tempPtr->boundary_tag), getSize(&tempPtr->free_list_node._next->boundary_tag));
      tempPtr->free_list_node._next->free_list_node._prev = (void *)tempPtr->free_list_node._next;
      tempPtr->free_list_node._next->free_list_node._next = (void *)tempPtr->free_list_node._next;
      //fprintf(stderr, "BLAH7\n");
      return (void *)tempPtr + sizeof(BoundaryTag);
    }
    tempPtr = tempPtr->free_list_node._next;    
   }
   //fprintf(stderr, "Getting new Chunk %d\n", chunkNumber); 
   FreeObject * newChunk = getNewChunk(ARENA_SIZE);
   setSize(&newChunk->boundary_tag, ARENA_SIZE - (2*sizeof(BoundaryTag)));
   newChunk->boundary_tag._leftObjectSize = 0;
   setAllocated(&newChunk->boundary_tag, NOT_ALLOCATED);
   newChunk->free_list_node._next = _freeList->free_list_node._next;
   _freeList->free_list_node._next = newChunk;
   chunkNumber++;
   i++;
  }while(i <= 1);
  pthread_mutex_unlock(&mutex);
  return NULL;
}

/**
 * @brief TODO: PART 2
 * This funtion takes a pointer to memory returned by the program, and
 * appropriately reinserts it back into the free list.
 * You will have to manage all coalescing as needed
 *
 * @param ptr
 */
static void freeObject(void *ptr)
{
  //fprintf(stderr,"%d %d %d %d", *test, *(test - 16), *(test - 8), *(test + 32));
  FreeObject* origin;
  origin = ((void *)ptr - sizeof(BoundaryTag));
  FreeObject* left;
  FreeObject* right;

  int leftObjSize = (int)origin->boundary_tag._leftObjectSize; 
  left = ((void *)origin - leftObjSize);
  int originSize = (int) getSize(&origin->boundary_tag);
  right = ((void *)origin + originSize);

//  fprintf(stderr, "Size and Allocs %d %d %d\n",left->_objectSizeAndAlloc, origin->_objectSizeAndAlloc, right->_objectSizeAndAlloc );
//   fprintf(stderr, "%p %p %p\n", &left, &origin, &right);
//   fprintf(stderr, "Sizes %d %d %d\n", getSize(&left->boundary_tag), getSize(&origin->boundary_tag), getSize(&right->boundary_tag));
//  fprintf(stderr, "isAllocs %d %d %d\n", isAllocated(&left->boundary_tag), isAllocated(&origin->boundary_tag), isAllocated(&right->boundary_tag));

  if((isAllocated(&left->boundary_tag) == NOT_ALLOCATED) && (isAllocated(&right->boundary_tag) == NOT_ALLOCATED)){
    right->free_list_node._next->free_list_node._prev = right->free_list_node._prev;
    right->free_list_node._prev->free_list_node._next = right->free_list_node._next;
    setSize(&left->boundary_tag, getSize(&left->boundary_tag) + getSize(&origin->boundary_tag) + getSize(&right->boundary_tag));
  } 
  else if(isAllocated(&left->boundary_tag) == NOT_ALLOCATED){
    setSize(&left->boundary_tag, getSize(&left->boundary_tag) + getSize(&origin->boundary_tag));
  } 
  else if(isAllocated(&right->boundary_tag) == NOT_ALLOCATED){
    right->free_list_node._next->free_list_node._prev = origin;
    right->free_list_node._prev->free_list_node._next = origin;
    origin->free_list_node._prev = right->free_list_node._prev;
    origin->free_list_node._next = right->free_list_node._next;
    setSize(&origin->boundary_tag, getSize(&origin->boundary_tag) + getSize(&right->boundary_tag));
    setAllocated(&origin->boundary_tag, NOT_ALLOCATED);
  }
  else{
    _freeList->free_list_node._next->free_list_node._prev = origin;
    origin->free_list_node._next = _freeList->free_list_node._next;
    _freeList->free_list_node._next = origin;
    origin->free_list_node._prev = _freeList;
    setAllocated(&origin->boundary_tag, NOT_ALLOCATED);
  }
}

void print()
{
  printf("\n-------------------\n");

  printf("HeapSize:\t%zd bytes\n", _heapSize);
  printf("# mallocs:\t%d\n", _mallocCalls);
  printf("# reallocs:\t%d\n", _reallocCalls);
  printf("# callocs:\t%d\n", _callocCalls);
  printf("# frees:\t%d\n", _freeCalls);

  printf("\n-------------------\n");
}

void print_list()
{
    printf("FreeList: ");
    if (!_initialized) 
        initialize();
    FreeObject *ptr = _freeList->free_list_node._next;
    while (ptr != _freeList) {
        long offset = (long)ptr - (long)_memStart;
        printf("[offset:%ld,size:%zd]", offset, getSize(&ptr->boundary_tag));
        ptr = ptr->free_list_node._next;
        if (ptr != NULL)
            printf("->");
    }
    printf("\n");
}

void increaseMallocCalls() { _mallocCalls++; }

void increaseReallocCalls() { _reallocCalls++; }

void increaseCallocCalls() { _callocCalls++; }

void increaseFreeCalls() { _freeCalls++; }

//
// C interface
//

extern void* malloc(size_t size)
{
  pthread_mutex_lock(&mutex);
  increaseMallocCalls();
  
  return allocateObject(size);
}

extern void free(void *ptr)
{
  pthread_mutex_lock(&mutex);
  increaseFreeCalls();
  
  if (ptr == 0) {
    // No object to free
    pthread_mutex_unlock(&mutex);
    return;
  }
  
  freeObject(ptr);
}

extern void* realloc(void *ptr, size_t size)
{
  pthread_mutex_lock(&mutex);
  increaseReallocCalls();

  // Allocate new object
  void *newptr = allocateObject(size);

  // Copy old object only if ptr != 0
  if (ptr != 0) {

    // copy only the minimum number of bytes
    FreeObject *o = (FreeObject *)((char *) ptr - sizeof(BoundaryTag));
    size_t sizeToCopy = getSize(&o->boundary_tag);
    if (sizeToCopy > size) {
      sizeToCopy = size;
    }

    memcpy(newptr, ptr, sizeToCopy);

    //Free old object
    freeObject(ptr);
  }

  return newptr;
}

extern void* calloc(size_t nelem, size_t elsize)
{
  pthread_mutex_lock(&mutex);
  increaseCallocCalls();
    
  // calloc allocates and initializes
  size_t size = nelem * elsize;

  void *ptr = allocateObject(size);

  if (ptr) {
    // No error
    // Initialize chunk with 0s
    memset(ptr, 0, size);
  }

  return ptr;
}

