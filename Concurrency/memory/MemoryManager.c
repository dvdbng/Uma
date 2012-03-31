/*
 * MemoryManager.c
 *
 *  Created on: 09/03/2012
 *      Author: alumno
 */
#include <stdlib.h>
#include <stdio.h>
#include "MemoryManager.h"

void Create(T_handler* ptrHandler){
    struct T_Node * tn ;

    //pointer to struct node:
    (*ptrHandler) = ((struct T_Node*) malloc(sizeof (struct T_Node)));
    (*ptrHandler)->end = MAX;
    (*ptrHandler)->next = NULL;
    (*ptrHandler)->start = 0;
}



/*
 * Destroy
 * Author: Loubna Channouf
 *
 */
void Destroy(T_handler* handler){
    T_handler des;
    if ( des = (*handler) -> next){
        Destroy(&des);
    }
    free(*handler);
    *handler = 0;
}

/*
 * Allocate
 * Author: Stefanie Salomon
 *
 */
void Allocate(T_handler* ptrHandler, unsigned size, unsigned* ad, unsigned* ok){
    T_handler n = *ptrHandler;

    int dispon = (n)->end - (n)->start +1;
    if (size <= dispon){
        *ad = (n)->start;
        *ok = 1;
        if (size < dispon){
            n->start += size;
        }else{
            *ptrHandler = n->next;
            free(n);
        }
    }else{
        if (n->next != NULL){
            Allocate(&n->next, size, ad, ok);
        }else{
            *ok=0;
        }
    }
}



/*
 * Deallocate (create_node + compactate)
 * Author: David Bengoa
 *
 */

T_handler create_node(unsigned start, unsigned end, T_handler next){
    T_handler node = (T_handler)malloc(sizeof(T_handler));
    node->start = start;
    node->end = end;
    node->next = next;
    return node;
}

unsigned compactate(T_handler ant){
    if(ant){
        T_handler sig = ant->next;
        if(sig && ant->end == sig->start-1){
            ant->end = sig->end;
            ant->next = sig->next;
            free(sig);
            return 1;
        }
    }
    return 0;
}

void Deallocate(T_handler* handler, unsigned size ,unsigned ad){
    T_handler *node = handler;

    T_handler ant_tmp = NULL;
    T_handler *ant = &ant_tmp;

    while(*node){
        if(ad < (*node)->start){ // Assumes size > 0
            *node = create_node(ad,ad+size-1,*node);
            if(compactate(*ant)){
                compactate(*ant);
            }else{
                compactate(*node);
            }
            break;
        }else{
            ant = node;
            node = &(*node)->next;
        }
    }
    if(!*node){
        if(!*ant){ // Special case with all memory allocated (Deallocate at the start)
            T_handler new_node = create_node(ad,ad+size-1,NULL);
            *handler = new_node;
        }else if((*ant)->end <= ad){ // Node needs to be inserted at the end
            T_handler new_node = create_node(ad,ad+size-1,NULL);
            (*ant)->next = new_node;
            compactate(*ant);
        }
    }
}

void Show (T_handler handler){
    printf("Map: ");
    while(handler){
        printf("[%d, %d]", handler->start, handler->end);
        handler = handler->next;
    }
    printf("\n");
}

int main () {
    T_handler handler;
    unsigned ok;
    unsigned ad;
    printf("Uno\n");
    Create(&handler);
    Show(handler);

    Allocate(&handler,50,&ad,&ok);
    Allocate(&handler,50,&ad,&ok);
    Show(handler);
    Deallocate(&handler,25,0);
    Show(handler);
    Deallocate(&handler,25,50);
    Show(handler);
    Deallocate(&handler,25,25);
    Show(handler);
    Deallocate(&handler,25,75);
    Show(handler);

    printf("Dos\n");

    Allocate(&handler,50,&ad,&ok);
    if (ok) {
        Show(handler);
        printf("Starting address is: %d\n", ad);
    } else {
        printf("Unable to allocate such a memory\n");
    }

    Deallocate(&handler, 20,0);
    Show (handler);

    Allocate(&handler,25,&ad,&ok);
    if (ok) {
        Show(handler);
        printf("Starting address is: %d\n", ad);
    } else {
        printf("Unable to allocate such a memory\n");
    }

    Deallocate(&handler,10,50);
    Show(handler);

    Allocate(&handler,25,&ad,&ok);
    if (ok) {
        Show(handler);
        printf("Starting address is: %d\n", ad);
    } else {
        printf("Unable to allocate such a memory\n");
    }

    Deallocate(&handler, 20,75);
    Show(handler);

    Destroy(&handler);
    Show (handler);


    return 0;
}

