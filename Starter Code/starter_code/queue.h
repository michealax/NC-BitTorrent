#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "sha.h"
#include "bt_parse.h"

typedef struct node_s{
	void *data;
	struct node_s *next;
} node_t;

typedef struct queue_ {
	node_t *head;
	node_t *tail:
	int num;
} queue_t;

queue_t init_queue();
void enqueue(queue_t *queue, void *data);
void *dequeue(queue_t *queue);
void free_queue(queue_t *queue);


#endif // QUEUE_H
