#include <stdlib.h>
#include <stdio.h>
// #include "linkedList.h"
#include "poker.h"
#include <string.h>
#include "pokerHands.h"
#include "interfaz.h"
// #include <unistd.h>
// #include<windows.h>

mazo* crear_mazo () {
    
    int j = 0;
    mazo *nuevo_mazo = malloc(sizeof(mazo));
    int k = 0;

    for (j = 0; j<4; j++) {
        
        for (int i = 1; i<=13; i++) {
             carta nueva_carta;
            
            nueva_carta.tipo_carta = j;
            nueva_carta.valor_carta = i;
            nueva_carta.eliminado = 1;

            (*(nuevo_mazo)).baraja[k] = nueva_carta;
            k++;
        }
    }

    (*(nuevo_mazo)).restantes = 52;
    return nuevo_mazo;
}

node* repartir(mazo* baraja, int cantidad, node* mano) {

    if (cantidad <= (*baraja).restantes) {
        time_t t;
        srand((unsigned) time(&t));
        
        for (int i = 0 ; i < cantidad ; i++) {
            
            carta nueva_carta;
            int random = rand() % 52;
            
            if ( (*baraja).baraja[random].eliminado == 0) {
                i--;
                continue;
            }

            nueva_carta =  (*baraja).baraja[random];
            mano = insert(nueva_carta, mano);

            (*baraja).baraja[random].eliminado = 0;
            (*baraja).restantes --;        
    }

    }
    return mano;

}

void apuesta (juego* juego, jugador* jugador, pot_node* bote) {

    printf("\n\n\n\n");
    printf("Es el turno de %s su dinero actual es: %d\n", jugador -> nombre, jugador -> dinero);

    printf("Las cartas sobre la mesa son: \n\n");
    imprimir_mano(juego->mesa);

    printf("Su mano es: \n");
    imprimir_mano(jugador -> mano);

    //revisa en cual bote puede apostar el jugador

    pot_node* bote_actual = get_pot(bote, jugador->dinero, jugador->id);

    while (1) {

        if (jugador -> dinero == 0) {
            int inutil = 0;
            printf("Dinero en juego para este bote: %d\n", bote_actual->dinero);
            printf("Se encuentra All in, presione cualquier tecla para continuar.\n");
            scanf("%d", &inutil);
            break;
        }

        int apuesta;
        printf("Dinero en juego para este bote: %d\n", bote_actual->dinero);
        printf("¿Cuanto desea apostar? La apuesta mínima es: %d \n para retirarse inserte un -1 \n", bote_actual->apuesta_minima);
        scanf("%d", &apuesta);

        //pendiente: condiciones de apuesta

        if (apuesta == -1) {
            jugador -> en_ronda = False;
            juego -> jugadores_en_ronda -= 1;
            break;
        }

        else if (apuesta > jugador -> dinero) {
            printf(" \n\n\nNo puede apostar dinero que no tiene. su saldo actual es: %d \n", jugador -> dinero);
        }

        else if (apuesta < bote_actual -> apuesta_minima) {
            printf(" \n\n\nLa apuesta deber ser igual o mayor que %d \n", bote_actual->apuesta_minima);
        }
        
        else {
            bote_actual -> apuesta_minima = apuesta;
            bote_actual -> dinero += apuesta;

            jugador -> dinero -= apuesta;
            jugador -> en_ronda = True;
            break;
        }

    }
    printf("\n \n \n \n \n");
}

void cargar_jugadores_en_ronda(jugador* jugadores, int cantidad_jugadores, int* cantidad_jugadores_en_ronda) {

    int j = 0;

    for (int i = 0; i < cantidad_jugadores; i++) {

        if ( (jugadores+i)->dinero > 0 ) {
            (jugadores + i) -> en_ronda = True;
            j++;
        }
        else {
            (jugadores + i) -> en_ronda = False;
        }
    }
    *cantidad_jugadores_en_ronda = j;
}

int valor_de_mano (node* mano, node* mesa) {

    int valor_mano = comprobar_straight_flush(mano, mesa);


    if (valor_mano != 0) {
        return valor_mano;
    }

    valor_mano = comprobar_four_of_a_kind(mano, mesa);

    if (valor_mano != 0) {
        return valor_mano;
    }

    valor_mano = comprobar_full_house(mano, mesa);

    if (valor_mano != 0) {
        return valor_mano;
    }

    valor_mano = comprobar_flush(mano, mesa);

    if (valor_mano != 0) {
        return valor_mano;
    }

    valor_mano = comprobar_straight(mano, mesa);

    if (valor_mano != 0) {
        return valor_mano;
    }

    valor_mano = comprobar_three_of_a_kind(mano, mesa);

    if (valor_mano != 0) {
        return valor_mano;
    }  

    valor_mano = comprobar_two_pair(mano, mesa);

    if (valor_mano != 0) {
        return valor_mano;
    }

    valor_mano = comprobar_one_pair(mano, mesa);

    if (valor_mano != 0) {
        return valor_mano;
    }     

    return NoPair;
}

void repartir_botines (jugador* jugadores, juego* juego , pot_node* bote) {

    pot_node* cur = bote;

    do {

        int mejor_mano = 10;
        int cantidad_de_ganadores = 0;
        int ganadores[5];

        for (int i = 0; i < cur->cantidad_jugadores; i++) {

            int id = *((cur->jugadores) + i);



            node* hand = (jugadores + id) -> mano;

            int mano = valor_de_mano(hand, juego->mesa);

            if (mano < mejor_mano) {

                cantidad_de_ganadores = 1;
                ganadores[0] = id;
                mejor_mano = mano;

            }
            else if (mano == mejor_mano) {

                ganadores[cantidad_de_ganadores] = id;
                cantidad_de_ganadores += 1;
            }

        }

        for (int i = 0; i<cantidad_de_ganadores; i++) {

            int id = ganadores[i];

            printf("\n\nEl jugador %s ha ganado %d\n\n", (jugadores+id)->nombre, (cur->dinero)/cantidad_de_ganadores);

            (jugadores + id) -> dinero += (cur->dinero)/cantidad_de_ganadores;

            sleep(1);

        }

        cur = cur -> next;

    } while (cur != NULL);

}

//inicia el juego, todas las variables de los jugadores ya están inicializadas
void jugar (jugador* jugadores, int cantidad_jugadores) {
    
    juego juego;
    // cada ciclo de este while es una ronda completa
    while (True) {

        pot_node *bote = makeListpot_node(0, 0);

        juego.jugadores_en_ronda = cantidad_jugadores;
        mazo *mazo = crear_mazo();

        //cartas iniciales sobre la mesa
        juego.mesa = NULL;
        juego.mesa = repartir(mazo, 2, juego.mesa);
        juego.cantidad_cartas = 2;
        juego.apuesta_minima = 0;
        int cartas_por_jugador = 2;

        cargar_jugadores_en_ronda(jugadores, cantidad_jugadores, &juego.jugadores_en_ronda);
        if (juego.jugadores_en_ronda == 1) {
            break;
        }
        //se reparte 2 cartas a cada jugador
        for (int i = 0; i < cantidad_jugadores; i++) {

            if ((jugadores + i) -> en_ronda) {
    
                (jugadores + i) -> mano =  repartir(mazo, 2, (jugadores + i) -> mano);
                
                apuesta(&juego, jugadores+i, bote);
            }
        }

        //se reparten cartas tres veces más
        for (int i = 0; i < 3; i++) {

            juego.mesa = repartir(mazo, 1, juego.mesa);
            juego.cantidad_cartas += 1;

            for (int j = 0; j < cantidad_jugadores; j++) {

                if ((jugadores + j) -> en_ronda) {

                    (jugadores + j) -> mano =  repartir(mazo, 1, (jugadores + j) -> mano);
                    apuesta(&juego, jugadores+j, bote);
                }                
            }
        }
        //Se revisa quien gano
        repartir_botines(jugadores, &juego, bote);


        //se limpian todas las variables


        break;
    }
}

void f_main () {

    mensaje_bienvenida();

    printf("¿Que desea hacer?\n");
    printf("\n(1)   ¡Jugar!");
    printf("\n(2)   Reglas");
    printf("\n(3)   Mejores manos ");
    printf("\n(4)   Salir\n");
    printf("Elija una opción (1-4):  ");

    int opcion;

    while (1) {
        
        opcion = pedir_input();

        if (opcion >= 1 && opcion <= 4) {

            break;
        }

        printf("Debe insertar un valor entre 1 y 4\n");
    }
    
    switch (opcion) {

        case 1:;
           
            int dinero_inicial = pedir_dinero_inicial();
            int cantidad_de_jugadores = pedir_cantidad_de_jugadores();
            jugador* jugadores = pedir_nombres(cantidad_de_jugadores);

            for (int i =0; i < cantidad_de_jugadores; i++) {
                (jugadores+i) -> dinero = dinero_inicial;
                (jugadores+i) -> en_ronda = True;
                (jugadores+i) -> mano = NULL;
                (jugadores+i) -> id = i;
            }            

            jugar(jugadores, cantidad_de_jugadores);

            break;

        case 2:;

            printf("\n\nEn el siguiente enlace se pueden encontrar las reglas del juego:https://bicyclecards.com/how-to-play/basics-of-poker\n\n");
            break;

        case 3:
            break;

        case 4:
            break;

        }
    }

void main() {
    f_main();
}