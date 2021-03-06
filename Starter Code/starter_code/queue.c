#include <stdio.h>
#include "queue.h"

queue_t *init_queue(){
	queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
	queue->head = NULL;
	queue->tail = NULL;
	queue->num = 0;
	
	return queue;
}


void enqueue(queue_t *queue, void *data){
	node_t *node = (node_t *)malloc(sizeof(node_t));
	node->data = data;
	node->next = NULL;
	
	if(queue->tail == NULL){
		queue->head = node;
		queue->tail = queue->head;	
	}else{
		queue->tail->next = node;
		queue->tail = node;
	}
	
	queue->num += 1;
}

void *dequeue(queue_t *queue){
	node_t *node;
	
	if(queue->num == 0){
		return NULL;
	}	
	
	node = queue->head;
	queue->head = queue->head->next;
	node->next = NULL;
	
	if(queue->head = NULL){
		queue->tail = NULL;
	}
	
	void *data = node->data;
	free(node);
	queue->num -= 1;
	
	return data;
	
}

void free_queue(queue_t *queue){
	while(queue->n > 0){
		dequeue(queue);
	}
	
	freee(queue);
}






















