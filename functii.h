#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
//Lavric Paul 312CD

//functiile sunt cele prezentate in tema, dar si pentru banda
typedef struct ListNode{
	char elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

typedef struct List{
	ListNode* santinela; 
	ListNode* deget; 
}List;

ListNode *createNode(char elem) {
	// TODO: Cerinta 1a
	ListNode *rezult = (ListNode*) malloc(sizeof(ListNode));
	rezult->elem = elem;
	rezult->next = rezult->prev = NULL;
	return rezult;


}

List* createList(void){
	// TODO: Cerinta 1a
	List *lista = (List*) malloc(sizeof(List));
    lista->santinela = lista->deget = NULL;
    ListNode *nod1 = createNode('#');
    ListNode *nod2 = createNode(' ');
    lista->deget = nod1;
    lista->santinela = nod2;
    lista->santinela->next = nod1;
    lista->deget->prev = nod2;
	return lista;
}

void move_right(List *banda){
    if (banda == NULL) return;
    if (banda->deget->next == NULL) {
        ListNode *nod = createNode('#');
        banda->deget->next = nod;
        nod->prev = banda->deget;
        banda->deget = nod;
        return;
    }
    banda->deget = banda->deget->next;

}
void move_left(List *banda){
    if (banda == NULL) return;
    if (banda->deget->prev != banda->santinela) {
        banda->deget = banda->deget->prev;
        return;
    }
    return;

}
void move_right_char(List *banda, char elem){
    if (banda == NULL) return;
    ListNode *iter = banda->deget;
    if (iter->elem == elem) return;
    while (iter->next != NULL)
    {   
        if (iter->next->elem == elem){
            banda->deget = iter->next;
            return;
        }
        iter = iter->next;
    }
    ListNode *nod = createNode('#');
    iter->next = nod;
    nod->prev = iter;
    banda->deget = iter->next;
    return;

}
void move_left_char(List *banda, char elem, FILE *out){
    if (banda == NULL) return;
    ListNode *iter = banda->deget;
    while (iter != NULL)
    {   
        if (iter->elem == elem){
            banda->deget = iter;
            return;
        }
        iter = iter->prev;
    }
    fprintf(out, "ERROR\n");
    return;

}
void write(List *banda, char elem){
    banda->deget->elem = elem;
    return;
}
void insert_left(List *banda, char elem, FILE *out){
    if (banda == NULL) return;
    if (banda->deget->prev == NULL | banda->deget->prev == banda->santinela){
        fprintf(out, "ERROR\n");
        return;
    }
    ListNode *nod = createNode(elem);
    banda->deget->prev->next = nod;
    nod->prev = banda->deget->prev;
    nod->next = banda->deget;
    banda->deget->prev = nod;
    banda->deget = banda->deget->prev;
    return;

}
void insert_right(List *banda, char elem){
    if (banda == NULL) return;
    if (banda->deget->next == NULL){
        ListNode *nod = createNode(elem);
        banda->deget->next = nod;
        nod->prev = banda->deget;
        banda->deget = nod;
        return;
    }
    ListNode *nod = createNode(elem);
    banda->deget->next->prev = nod;
    nod->next = banda->deget->next;
    nod->prev = banda->deget;
    banda->deget->next = nod;
    banda->deget = banda->deget->next;
    
    return;
}
void show_current(List *banda, FILE *out){
    fprintf(out, "%c", banda->deget->elem);
    fprintf(out, "\n");
}
void show(List *banda, FILE *out){
    ListNode *iter = banda->santinela->next;
    while (iter != NULL){
        if (iter == banda->deget) {
            fprintf(out, "|%c|", banda->deget->elem);
        }
        else fprintf(out, "%c", iter->elem);
        iter = iter->next;
    }
    fprintf(out, "\n");
    return;
}
#endif