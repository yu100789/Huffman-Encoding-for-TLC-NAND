#include <stdio.h>
#include <stdlib.h>

#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) ((i - 1) / 2)

typedef struct Heap {
  int *array;
  int size;
  int capacity;
} Heap;

Heap *create_heap(int capacity) {
  Heap *heap = (Heap *)malloc(sizeof(Heap));
  heap->capacity = capacity;
  heap->size = 0;
  heap->array = (int *)malloc(capacity * sizeof(int));
  return heap;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void heapify_down(Heap *heap, int i) {
  int largest = i;
  int left = LEFT(i);
  int right = RIGHT(i);

  if (left < heap->size && heap->array[left] > heap->array[largest])
    largest = left;

  if (right < heap->size && heap->array[right] > heap->array[largest])
    largest = right;

  if (largest != i) {
    swap(&heap->array[i], &heap->array[largest]);
    heapify_down(heap, largest);
  }
}

void heapify_up(Heap *heap, int i) {
  while (i > 0 && heap->array[PARENT(i)] < heap->array[i]) {
    swap(&heap->array[i], &heap->array[PARENT(i)]);
    i = PARENT(i);
  }
}

void insert(Heap *heap, int key) {
  heap->array[heap->size] = key;
  heap->size += 1;
  heapify_up(heap, heap->size - 1);
}

int extract_max(Heap *heap) {
  int max = heap->array[0];
  heap->array[0] = heap->array[heap->size - 1];
  heap->size -= 1;
  heapify_down(heap, 0);
  return max;
}

int main() {
  Heap *heap = create_heap(100);
  insert(heap, 10);
  insert(heap, 20);
  insert(heap, 15);
  insert(heap, 40);

  printf("%d\n", extract_max(heap));
  printf("%d\n", extract_max(heap));
  printf("%d\n", extract_max(heap));
  printf("%d\n", extract_max(heap));

  return 0;
}
