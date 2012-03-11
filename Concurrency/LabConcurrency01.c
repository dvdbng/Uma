            /*
 ============================================================================
 Name        : LabConcurrency01.c
 Author      : Llopis. Translated by Sergio Gálvez Rojas.
 Version     :
 Copyright   : UMA. ETSII.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "MemoryManager.h"

T_handler create_node(unsigned start, unsigned end, T_handler next){
    T_handler node = (T_handler)malloc(sizeof(T_handler));
    node->start = start;
    node->end = end;
    node->next = next;
    return node;
}

void Create(T_handler* handler){
    T_handler node = create_node(0, MAX, NULL);
    *handler = node;
}

void Destroy(T_handler* handler){
    T_handler tmp;
    while(*handler){
        tmp = (*handler)->next;
        free(*handler);
        *handler = tmp;
    }
    *handler = 0;
}

void Allocate(T_handler* handler, unsigned size, unsigned* ad, unsigned* ok){
    printf("Allocate %d\n", size);
    T_handler node = *handler;
    if(node){
        unsigned avaliable = node->end - node->start +1;
        if(avaliable >= size){
            *ok = 1;
            *ad = node->start;
            if(avaliable==size){
                *handler = node->next;
                free(node);
            }else{
                node->start += size;
            }
        }else{
            Allocate(&node->next, size, ad, ok);
        }
    }else{
        *ok = 0;
    }
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
    printf("DeAllocate %d in %d\n", size, ad);
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

