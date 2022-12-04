#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poker.h"

pot_node* makeListpot_node (int apuesta_minima, int dinero) {

	pot_node* newElement = malloc(sizeof(pot_node));

	newElement -> cantidad_jugadores = 0;
    newElement -> apuesta_minima = apuesta_minima;
    newElement -> dinero = dinero;
    newElement -> jugadores = malloc(20);

	newElement -> next = NULL;

	return newElement;
}

void insert_jugador (int id, pot_node* bote) {

    int cantidad = bote -> cantidad_jugadores;
    int no_adentro = True;

    
    for (int i = 0; i<cantidad; i++) {
        // printf("%d id: %d", *((bote -> jugadores) + i), id);
        if (*((bote -> jugadores) + i) == id) {

            no_adentro = False;
            break;
        }
    }

    if (no_adentro) {
        *((bote -> jugadores) + cantidad) = id;
        (bote->cantidad_jugadores)++;
    }



}

//Busca en la lista de botes por uno en el que el jugador pueda apostar
pot_node* get_pot (pot_node* head, int dinero, int jugador_id) {

    pot_node* cur = head;

    do {

        if (cur->apuesta_minima <= dinero) {

            insert_jugador(jugador_id, cur);
            return cur;
        }

        cur = cur -> next;

    } while (cur != NULL);

    //Si se llega aqui se debe crear un bote nuevo
    pot_node* nuevo = NULL;
    nuevo = insert_pot(0, 0, jugador_id, nuevo);

    cur = nuevo;

    return cur;
}

pot_node* insert_pot (int apuesta_minima, int dinero, int jugador_inicial, pot_node * head) {

	pot_node* current = head;
	pot_node* new = makeListpot_node(apuesta_minima, dinero);

    insert_jugador(jugador_inicial, new);

	if (head == NULL) {
		
		return new;
	}

	while (current -> next != NULL){

		current = current -> next;
	}	

	current -> next = new;
	return head;
}
