#include <stdio.h>
#include <stdlib.h>

#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) ((i - 1) / 2)

typedef struct alphabet {
  char n;
  int freq;
} alphabet;

typedef struct Heap {
  alphabet *array;
  int size;
  int capacity;
} Heap;

int g_alphabet_treeIndex[255] = {0};

Heap *create_heap(int capacity) {
  Heap *heap = (Heap *)malloc(sizeof(Heap));
  heap->capacity = capacity;
  heap->size = 0;
  heap->array = (alphabet *)malloc(capacity * sizeof(alphabet));
  return heap;
}

// void swap(int *a, int *b) {
//   int temp = *a;
//   *a = *b;
//   *b = temp;
// }
void swap(alphabet *a, alphabet *b) {
  alphabet temp = *a;
  *a = *b;
  *b = temp;
}

void heapify_down(Heap *heap, int i) {
  int largest = i;
  int left = LEFT(i);
  int right = RIGHT(i);

  if (left < heap->size && heap->array[left].freq > heap->array[largest].freq)
    largest = left;

  if (right < heap->size && heap->array[right].freq > heap->array[largest].freq)
    largest = right;

  if (largest != i) {
    swap(&heap->array[i], &heap->array[largest]);
    heapify_down(heap, largest);
  }
}

void heapify_up(Heap *heap, int i) {
  while (i > 0 && heap->array[PARENT(i)].freq < heap->array[i].freq) {
    swap(&heap->array[i], &heap->array[PARENT(i)]);
    i = PARENT(i);
  }
}

// void insert(Heap *heap, int key) {
//   heap->array[heap->size] = key;
//   heap->size += 1;
//   heapify_up(heap, heap->size - 1);
// }
void insert(Heap *heap, int freq, char n) {
  heap->array[heap->size].freq = freq;
  heap->array[heap->size].n = n;
  g_alphabet_treeIndex[n] = heap->size;
  heap->size += 1;
  heapify_up(heap, heap->size - 1);
}
int extract_max(Heap *heap) {
  int max = heap->array[0].n;
  heap->array[0] = heap->array[heap->size - 1];
  heap->size -= 1;
  heapify_down(heap, 0);
  return max;
}

int main() {
  Heap *heap = create_heap(100);
  char aa[] = "asdasdbsdfzaasdasaasdasdasvbbsadsgfebb";
  insert(heap, 90, 'a');
  insert(heap, 0, 'b');
  insert(heap, 15, 'c');
  insert(heap, 40, 'd');
  insert(heap, 20,  'f');
  printf("%c\n", extract_max(heap));
  printf("%c\n", extract_max(heap));
  printf("%c\n", extract_max(heap));
  printf("%c\n", extract_max(heap));
  printf("%c\n", extract_max(heap));
  
  return 0;
}
