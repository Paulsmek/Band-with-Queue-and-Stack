#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Lavric Paul 312CD

#include "functii.h"
#include "coada.h"
#include "stiva.h"

//functie de adaugat in coada
TQueue *add(TQueue *queue, char *c){
    char *p = strtok(c, " ,.\n");
    int ok = 0;
    while (p){
        if (ok != 0) {
            queue = enqueue(queue,ok,*p);
        }
        if (strcmp(p, "WRITE") == 0) ok = 1;
        if (strcmp(p, "INSERT_LEFT") == 0) ok = 2;
        if (strcmp(p, "INSERT_RIGHT") == 0) ok = 3;
        if (strcmp(p, "MOVE_LEFT") == 0) queue = enqueue(queue,4,'|');
        if (strcmp(p, "MOVE_RIGHT") == 0) queue = enqueue(queue,5,'|');
        if (strcmp(p, "MOVE_LEFT_CHAR") == 0) ok = 6;
        if (strcmp(p, "MOVE_RIGHT_CHAR") == 0) ok = 7;
        if (strcmp(p, "SHOW_CURRENT") == 0) queue = enqueue(queue,8,'|');
        if (strcmp(p, "SHOW") == 0) queue = enqueue(queue,9,'|');
        if (strcmp(p, "EXECUTE") == 0) queue = enqueue(queue,10,'|');
        if (strcmp(p, "UNDO") == 0) queue = enqueue(queue,11,'|');
        if (strcmp(p, "REDO") == 0) queue = enqueue(queue,12,'|');
        p=strtok(NULL, " ,.\n");
    }
    return queue;
}
//functie de undo
TStack *do_undo(TStack* undo, List *banda){
    banda->deget = undo->data;
    undo = pop(undo);
    return undo;
}
//functie de redo
TStack *do_redo(TStack* redo, List *banda){
    banda->deget = redo -> data;
    redo = pop(redo);
    return redo;
}

int main()
{
    //declar variabile 
    List *banda = createList();
    FILE *ptr = fopen("tema1.in", "r");
    FILE *ptr2 = fopen("tema1.out", "w");
    if (ptr == NULL) {
        printf("ERROR_FILE");
    }
    int num;
    char c[21];
    //realizez citirea din fisier
    fscanf(ptr, "%d", &num);
    fgets(c, 20, ptr);
    if (num > 0){
        fgets(c, 20, ptr);
    }
    TQueue *queue = create_queue(1, '1');
    queue = add(queue, c);
    //adaug in coada
    while (fgets(c, 20, ptr) != NULL){
         queue = add(queue, c);
        
    }
    //creez stivele de undo si redo
    TStack *undo = init();
    TStack *redo = init();
    TNode *iter = queue->head;
    queue->head = queue->head->next;
    free(iter);
    TNode *nod = queue->head;
    TNode *nod_exec = queue->head;
    //parcurg coada cu functii
    while (nod_exec->value > 7 && nod_exec->next != NULL) nod_exec = nod_exec->next;
    while (nod!=NULL){
        if (nod->value == 10){
            if (nod_exec->value == 1) write(banda, nod_exec->caracter);
            if (nod_exec->value == 2) insert_left(banda, nod_exec->caracter, ptr2);
            if (nod_exec->value == 3) insert_right(banda, nod_exec->caracter);
            if (nod_exec->value == 4){
                if(banda->deget->prev != banda->santinela) undo = push(undo, banda->deget);
                move_left(banda);
            }
            if (nod_exec->value == 5) undo = push(undo, banda->deget), move_right(banda);
            if (nod_exec->value == 6) undo = push(undo, banda->deget), move_left_char(banda, nod_exec->caracter, ptr2);
            if (nod_exec->value == 7) undo = push(undo, banda->deget), move_right_char(banda, nod_exec->caracter);
            if (nod_exec->next != NULL) nod_exec = nod_exec->next;
            while(nod_exec->value > 7 && nod_exec->next != NULL) nod_exec = nod_exec->next;
        }
        if (nod->value == 8) show_current(banda, ptr2);
        if (nod->value == 9) show(banda, ptr2);
        if (nod->value == 11) {
            redo = push(redo, banda->deget);
            undo = do_undo(undo, banda);
            
        }
        if (nod->value == 12){
           undo = push(undo, banda->deget);
           redo = do_redo(redo, banda);
        }
        nod = nod->next;
    }
    //eliberez memoria
    ListNode *iter2 = banda->santinela;
    while (iter2 != NULL){
        ListNode *dummy = iter2;
        iter2 = iter2->next;
        free(dummy);
    }
    TStack *iter_undo = undo;
    while (iter_undo != NULL){
        TStack *dummy1 = iter_undo;
        iter_undo = iter_undo->next;
        free(dummy1);
    }
    TStack *iter_redo = redo;
    while (iter_redo != NULL){
        TStack *dummy2 = iter_redo;
        iter_redo = iter_redo->next;
        free(dummy2);
    }

    TNode *iter3 = queue->head;
    while (iter3 != NULL){
        TNode *dummy3 = iter3;
        iter3 = iter3->next;
        free(dummy3);
    }

    //free(undo);
    //free(redo);
    free(banda);
    free(queue);
    //inchid fisierele
    fclose(ptr); 
    fclose(ptr2);
    return 0;

}