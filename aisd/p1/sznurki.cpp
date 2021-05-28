#include <iostream>

using namespace std;

typedef struct record {
  long long len;
  long long quan;
} record;

/* Debugging tools */
void print_heap(record* heap, int size, int strings) {
  for (int i = 1; i < size; i++) {
    printf("%d: %lld - %lld\n", i, heap[i].len, heap[i].quan);
  }
  printf("strings: %d\n", strings);
}

/* Heap functionality necessary for sorting */
void push_down(record* heap, int size, int i) {
  int max_child = i;
  do {
    i = max_child;
    int doublei = i * 2;
    if (doublei < size && heap[doublei].len > heap[max_child].len)
      max_child = doublei;
    if (doublei + 1 < size && heap[doublei + 1].len > heap[max_child].len)
      max_child = doublei + 1;
    swap(heap[i], heap[max_child]);
  } while (i != max_child);
}

void delete_max(record* heap, int size) {
  swap(heap[1], heap[size - 1]);
  push_down(heap, size - 1, 1);
}

void build_heap(record* heap, int size) {
  for (int i = size / 2; i > 0; i--)
    push_down(heap, size, i);
}

void heapsort(record* heap, int size) {
  int iter_num = size - 2;
  for (int i = 0; i < iter_num; i++) {
    delete_max(heap, size);
    size--;
  }
}

int binsearch(record* heap, int start, int end, int val) {
  int mid = (start + end) / 2;
  while (start <= end) {
    if (heap[mid].len == val)
      return mid;
    if (heap[mid].len > val)
      end = mid - 1;
    else
      start = mid + 1;
    mid = (start + end) / 2;
  }
  return -1;
}

int main() {
  int n;
  int max;
  int size = 1;
  int mem_size = 1;
  int strings = 0;
  record* heap = (record*)malloc(sizeof(record));
  scanf("%d", &n);
  for (long i = 0; i < n; i++) {
    long long d, nd;
    scanf("%lld %lld", &d, &nd);
    size += 1;
    heap = (record*)realloc((void*)heap, size * sizeof(record));
    heap[size - 1].len = d;
    heap[size - 1].quan = nd;
  }

  build_heap(heap, size);
  heapsort(heap, size);
  max = heap[size - 1].len;

  for (int i = 1; i < size; i++) {
    int val = heap[i].len;
    int quan = heap[i].quan;
    bool multiple_found = false;
    while (val < max && quan > 0) {
      if (quan % 2)
        strings++;
      val *= 2;
      quan /= 2;
      int pos = binsearch(heap, i + 1, size - 1, val);
      if (pos > 0) {
        multiple_found = true;
        heap[pos].quan += quan;
        break;
      }
    }
    if (val >= max && !multiple_found)
      while (quan > 0) {
        if (quan % 2)
          strings++;
        val *= 2;
        quan /= 2;
      }
  }

  printf("%d\n", strings);

  return 0;
}