#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poker.h"


node* makeListNode (carta* carta) {

	node* newElement = malloc(sizeof(node));

	newElement -> carta = carta;
	newElement -> next = NULL;
	return newElement;
}

node* insert (carta carta, node * head) {

	node* current = head;
    struct carta *c = malloc(sizeof(struct carta));
    *c = carta;

	node* new = makeListNode(c);

	if (head == NULL) {
		
		return new;
	}

	while (current -> next != NULL){

		current = current -> next;
	}	

	current -> next = new;
	return head;
}

int imprimir_carta(carta carta) {

    switch(carta.valor_carta) {
        case A:
            printf("A ");
            break;
        case J:
            printf("J ");
            break;
        case Q:
            printf("Q ");
            break;
        case K:
            printf("K ");
            break;
        default:
            printf("%d ",  carta.valor_carta);
    }

    switch(carta.tipo_carta) {
        case diamantes:
            printf("de diamantes");
            return 1;

        case trebol:
            printf("de trebol");
            return 1;

        case corazones:
            printf("de corazones");
            return 1;

        case espadas:
            printf("de espadas");
            return 1;

        default:
            return 0;
    }
}

void imprimir_mano (node* mano) {

	node* current = mano;

	while (current != NULL){
		imprimir_carta(*(current -> carta));
        printf("   ");

		current = current -> next;

	}	
    printf("\n");
}
