#ifndef _DOUBLE_LINKED_LIST2_H_
#define _DOUBLE_LINKED_LIST2_H_
#include <stdlib.h>
//Lavric Paul 312CD

typedef struct node {
    int value;
    char caracter;
    struct node* next;
} TNode, TSortedList;

typedef struct queue{
    TNode *head;
    TNode *tail;
    int size;
} TQueue;


TSortedList *coada_create_nod(int value, char caracter) {
    // TODO (se va completa la Cerința 2)
    TSortedList *rez = (TSortedList*) malloc(sizeof(TSortedList));
    rez->value = value;
    rez->caracter = caracter;
    rez->next = NULL; 
    return rez;
}

TQueue *create_queue(int value, char caracter){
    TQueue *rezz = (TQueue*) malloc(sizeof(TQueue));
    rezz->head = rezz->tail = coada_create_nod(value, caracter);
    rezz->size = 1;
    return rezz;
}

TQueue *enqueue(TQueue *queue, int value, char caracter){
    TNode *nod;
    if (queue == NULL) return create_queue(value, caracter);
    nod = coada_create_nod(value, caracter);
    queue->tail->next = nod;
    queue->tail = nod;
    queue->size++;
    if (caracter != '|') queue->tail->caracter = caracter;
    return queue;

}
TQueue *dequeue(TQueue *queue){
    TNode *nod;
    nod = queue->head;
    queue->head = queue->head->next;
    if (nod) free(nod);
    queue->size--;
    return queue;
    

}


#endif