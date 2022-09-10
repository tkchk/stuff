#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeap MinHeap;
struct MinHeap {
  int* arr;
  int size;
  int capacity;
};

int parent(int i) {
  return (i - 1) / 2;
}

int left_child(int i) {
  return (2 * i + 1);
}

int right_child(int i) {
  return (2 * i + 2);
}

int get_min(MinHeap* heap) {
  return heap->arr[0];
}

MinHeap* init_minheap(int capacity) {
  MinHeap* minheap = (MinHeap*) calloc(1, sizeof(MinHeap));
  minheap->arr = (int*) calloc(capacity, sizeof(int));
  minheap->capacity = capacity;
  minheap->size = 0;
  return minheap;
}

void free_minheap(MinHeap* heap) {
  if (!heap) {
    return;
  }
  free(heap->arr);
  free(heap);
}

MinHeap* insert_minheap(MinHeap *heap, int element) {
  if (heap->size == heap->capacity) {
    fprintf(stderr, "Cannot insert %d. Heap is full!\n", element);
  }
  heap->size++;
  heap->arr[heap->size - 1] = element;
  int curr = heap->size - 1;
  while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr]) {
    int temp = heap->arr[parent(curr)];
    heap->arr[parent(curr)] = heap->arr[curr];
    heap->arr[curr] = temp;
    curr = parent(curr);
  }
  return heap;
}

int main (int argc, char *argv[]){
  MinHeap* heap = init_minheap(20);
  return 0;
}

