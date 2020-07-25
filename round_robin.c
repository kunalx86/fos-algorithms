#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

typedef struct process {
	int id, n_cycles;
	struct process* next;
}process_t;

typedef struct queue {
	process_t* f;
	process_t* r;	
}queue_t;

queue_t* createQueue();

process_t* createProcess();

int isQueueEmpty(queue_t*_queue);

void enqueue(queue_t* _queue, process_t* _proc);

void dequeue(queue_t* _queue);

void round_robin(queue_t* _queue);

int main(void) {
	queue_t* _queue = createQueue();
	process_t* current = NULL;
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		current = createProcess();
		enqueue(_queue, current);
	}

	round_robin(_queue);

	// free(_queue);

	return 0;
}

queue_t* createQueue() {
	queue_t* _queue = (queue_t*) malloc(sizeof(queue_t));
	_queue->f = NULL;
	_queue->r = NULL;
	return _queue;
}

process_t* createProcess() {
	process_t* current = (process_t*) malloc(sizeof(process_t));
	scanf("%d %d", &(current->id), &(current->n_cycles));
	current->next = NULL;
	return current;
}

int isQueueEmpty(queue_t* _queue) {
	return (_queue->f == NULL && _queue->r == NULL);
}

void enqueue(queue_t* _queue, process_t* _proc) {
	if (!_queue->f && !_queue->r) {
		_queue->f = _proc;
		_queue->r = _proc;
	}
	else {
		_queue->r->next = _proc;
		_queue->r = _proc;
	}

}

void dequeue(queue_t* _queue) {
	process_t* to_del = NULL;
	if (_queue->f->n_cycles == 0 && !(_queue->f == _queue->r)) {
		to_del = _queue->f;
		_queue->f = to_del->next;
		free(to_del);
	}
	else if (_queue->f->n_cycles == 0 && _queue->f == _queue->r) {
		to_del = _queue->f;
		_queue->r = NULL; 
		_queue->f = NULL;
		free(to_del);
	}
	else if (_queue->f == _queue->r) {
		return;
	}
	else {
		to_del = _queue->f;
		_queue->f = to_del->next;
		to_del->next = NULL;
		enqueue(_queue, to_del);
	}
}

void round_robin(queue_t* _queue) {
	process_t* current;
	while(!isQueueEmpty(_queue)) {
		current = _queue->f;
		printf("Currently executing process %d and no. of cycles is %d will be decremented\n", current->id, current->n_cycles);
		current->n_cycles--;
		sleep(3);
		dequeue(_queue);
	}
}
