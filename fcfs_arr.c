#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef struct process {
    int id, arrive_time;
    unsigned short int executed;
} process_t;

void read_info(process_t* processes, int size) {
    for (int i = 0; i < size; ++i) {
        scanf("%d %d", &processes[i].id, &processes[i].arrive_time);
        processes[i].executed = false;
    }
}

void execute(process_t* process_) {
    printf("Executing process %d and arrive time %d\n", process_->id, process_->arrive_time);
    process_->executed = true;
}

void extract(process_t* processes, int size) {
    process_t* current = processes;
    while (current->executed) {
        current += 1;
    }
    for (int i = 0; i < size; ++i) {
        if ((processes[i].arrive_time < current->arrive_time) && (processes[i].executed == false)) {
            current = &processes[i];
        }
    }
    execute(current);
}

int main() {
    int size;
    process_t* processes;
    scanf("%d", &size);
    processes = (process_t*) malloc(size * sizeof(*processes));

    read_info(processes, size);

    for (int i = 0; i < size; ++i) {
        extract(processes, size);
    }

    return 0;
}