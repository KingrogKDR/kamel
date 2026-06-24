#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>

char *heap_start = NULL;
char *heap_end = NULL;

void *klloc(size_t size) {
  void *current = heap_start;
  if (heap_start + size > heap_end) {
    return NULL;
  }
  heap_start += size;
  return current;
}

int main(void) {
  size_t size = 4096;
  void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (mem == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  printf("Memory mmap: %p\n", mem);

  heap_start = mem;
  heap_end = heap_start + size;

  int *ptr1 = klloc(1024);

  printf("Memory block 1: %p\n", ptr1);

  int *ptr2 = klloc(1024);

  printf("Memory block 2: %p\n", ptr2);

  munmap(mem, size);

  return 0;
}
