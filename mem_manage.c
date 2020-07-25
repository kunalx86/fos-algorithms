#include <stdio.h>

#define SIZE 30
#define MEMORY 3

typedef struct {
  int arr[SIZE];
  int f, r;
} queue;

// typedef struct {
//   int arr[SIZE];
//   int top;
// } stack;

void enqueue(queue *q, int data) {
  if (q->f == -1) {
    q->f = 0;
  }
  q->arr[++q->r] = data;
}

int dequeue(queue *q) {
  int ret;
  if (q->f == q->r) {
    ret = q->arr[q->f]; 
    q->f = q->r = -1;
  }
  return q->arr[q->f++];
}

// void push(stack *s, int data) {
//   s->arr[++s->top] = data;
// }

// // The Pop here is repurposed to pop not the top most but the bottom-most page
// int pop(stack *s) {
//   return s->arr[s->top--];
// }

int search(int *current, int s) {
  for (int i = 0; i < MEMORY; ++i)
    if (current[i] == s) return i;
  return -1;
}

void removePage(int *current, int index) {
  for (int i = index; i < MEMORY; ++i)
    current[i] = current[i + 1];
}

void lru(int *ref, int n, queue *s) {
  int current[MEMORY], k = -1;
  // Iterate over all the referneces made
  for (int i = 0; i < n; ++i) {
    // Push the requied page onto the memory
    enqueue(s, ref[i]);
    if (ref[i] == s->arr[s->f] && i != 0)
      dequeue(s);
    printf("Page %d is pushed in memory\n", ref[i]);
    // Check if the page is present or not
    int present = search(current, ref[i]);
    // If present then simply push the page on top of stack
    if (present != -1) {
      printf("Page %d is present in memory\n", ref[i]);
    }
    // Else check if space is available or not to insert the page 
    else {
      // If the memory is full remove the least recently used page
      if (k == (MEMORY - 1)) {
        int popped = dequeue(s);
        int index = search(current, popped);
        removePage(current, index);
        current[k] = ref[i];
        printf("Popped least recently used %d page\n", popped);
      } 
      else {
        current[++k] = ref[i];
        printf("Page %d is inserted in memory\n", ref[i]);
      }
    }
  }
}

void fifo(int *ref, int n, queue *q) {
  int current[MEMORY], k = -1;
  for (int i = 0; i < n; ++i) {
    int present = search(current, ref[i]);
    if (present != -1) {
      printf("Page %d is present in memory\n", ref[i]);
    } 
    else {
      enqueue(q, ref[i]);
      printf("Page %d is enqueued in memory\n", ref[i]);

      if (k == (MEMORY - 1)) {
        int rem = dequeue(q);
        int index = search(current, rem);
        removePage(current, index);
        current[k] = ref[i];
        printf("Removed FIFO based %d page\n", rem);
      } 
      else {
        current[++k] = ref[i];
        printf("Page %d is inserted in memory\n", ref[i]);
      }
    }
  }
}

int main() {
  int references[] = { 
    100, 101, 100, 123, 104 
  }; 

  queue q1;
  q1.f = q1.r = -1;
  queue q2;
  q2.f = q2.r = -1;

  printf("LRU: \n");
  lru(references, sizeof(references) / sizeof(int), &q1);
  printf("FIFO: \n");
  fifo(references, sizeof(references) / sizeof(int), &q2);

  return 0;
}