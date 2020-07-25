#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

int current = -1;

typedef struct process {
    int id, arrive_time;
    // unsigned short int executed;
} process_t;

void swap(process_t* p1, process_t* p2) {
    process_t temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int parent(int i) {
    return (i - 1) / 2;
}

int left(int i) {
    return (2 * i + 1);
}

int right(int i) {
    return (2 * i + 2);
}

void heapify(process_t* heap, int i) {
    int _left = left(i);
    int _right = right(i);
    int _smallest = i;
    
    if (_left < current && heap[_left].arrive_time < heap[i].arrive_time) {
        _smallest = _left;
    }
    if (_right < current && heap[_right].arrive_time < heap[i].arrive_time) {
        _smallest = _right;
    }
    if (_smallest != i) {
        swap(&heap[i], &heap[_smallest]);
        heapify(heap, _smallest);
    }
}

void insert(process_t* heap, process_t __process) {
    current++;
    heap[current] = (__process);
    int i = current - 1;

    while(i != 0 && heap[parent(i)].arrive_time > heap[i].arrive_time) {
        swap(&heap[parent(i)], &heap[i]);
        i = parent(i);
    }
}

process_t extraxt_min(process_t* heap) {
    if (current == 1) {
        current--;
        return heap[0];
    }
    process_t ret = heap[0];
    heap[0] = heap[current - 1];
    current--;
    heapify(heap, 0);
    return (ret);
}


void read_info(process_t* heap, int size) {
    for (int i = 0; i < size; ++i) {
        process_t _process;
        scanf("%d %d", &_process.id, &_process.arrive_time);
        // _process.executed = false;
        insert(heap, _process);
    }
}

void execute(process_t _process) {
    printf("Executing process %d and arrive time %d\n", _process.id, _process.arrive_time);
    // process_->executed = true;
}

void extract(process_t* heap, int size) {
    for (int i = 0; i < size; ++i) {
        process_t current = extraxt_min(heap);
        execute(current);
    }
}

int main() {
    int size;
    process_t* heap;
    scanf("%d", &size);
    heap = (process_t*) malloc(size * sizeof(*heap));
    read_info(heap, size);
    extract(heap, size);
    return 0;
}