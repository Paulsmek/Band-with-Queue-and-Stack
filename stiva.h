#ifndef _DOUBLE_LINKED_LIST3_H_
#define _DOUBLE_LINKED_LIST3_H_
#include <stdlib.h>
//Lavric Paul 312CD

typedef struct stack {
ListNode *data;
struct stack *next;
}TStack;


TStack *initStack(ListNode *deget) {
TStack *stk = (TStack*) malloc(sizeof(TStack));
stk->data = deget;
stk->next = NULL;
return stk;
}

int isEmpty(TStack *s) {
return s == NULL;
}

TStack *push(TStack *s, ListNode *deget) {
TStack *top;
if (isEmpty(s)) return initStack(deget);
top = initStack(deget);
top->next = s;
return top;
}

TStack *pop(TStack *s) {
TStack *tmp;
if (isEmpty(s)) return s;
tmp = s;
s = s->next;
free(tmp);
return s;
}

TStack *init() {
return NULL;
}


#endif