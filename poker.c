#include <stdlib.h>
#include <stdio.h>
// #include "linkedList.h"
#include "poker.h"

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

void apuesta (juego* juego, jugador* jugador) {

    printf("Es el turno de %s su dinero actual es: %d\n", jugador -> nombre, jugador -> dinero);

    printf("Las cartas sobre la mesa son: \n");
    imprimir_mano(juego->mesa);

    printf("Su mano es: \n");
    imprimir_mano(jugador -> mano);

    while (1) {

        int apuesta;
        printf("¿Cuanto desea apostar? La apuesta mínima es: %d \n para retirarse inserte un -1 \n", juego->apuesta_minima);
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

        else if (apuesta < juego -> apuesta_minima) {
            printf(" \n\n\nLa apuesta deber ser igual o mayor que %d \n", juego->apuesta_minima);
        }
        
        else {
            juego -> apuesta_minima = apuesta;
            juego -> bote += apuesta;

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

void jugar () {
    
    int cantidad_jugadores = 2;
    int cantidad_jugadores_eliminados = 0;

    jugador* jugadores = malloc(cantidad_jugadores*sizeof(jugador));

    int dinero_inicial = 2000;

    jugador jugador1;
    jugador1.nombre = "Gabp";
    jugador1.dinero = dinero_inicial;
    jugador1.mano = NULL;
    jugador jugador2;
    jugador2.nombre = "yolo";
    jugador2.dinero = dinero_inicial;
    jugador2.mano = NULL;

    *jugadores = jugador1;
    *(jugadores + 1) = jugador2;


    while (cantidad_jugadores_eliminados != cantidad_jugadores - 1) {
        
        juego juego;
        juego.jugadores_en_ronda = cantidad_jugadores;
        mazo *mazo = crear_mazo();

        //cartas iniciales sobre la mesa
        juego.mesa = NULL;
        juego.mesa = repartir(mazo, 2, juego.mesa);
        juego.cantidad_cartas = 2;
        juego.apuesta_minima = 0;
        int cartas_por_jugador = 2;

        cargar_jugadores_en_ronda(jugadores, cantidad_jugadores, &juego.jugadores_en_ronda);
        //se reparte 2 cartas a cada jugador
        for (int i = 0; i < cantidad_jugadores; i++) {

            if ((jugadores + i) -> en_ronda) {
    
                (jugadores + i) -> mano =  repartir(mazo, 2, (jugadores + i) -> mano);
                
                apuesta(&juego, jugadores+i);
            }
        }

        //se reparten cartas tres veces más
        for (int i = 0; i < 3; i++) {

            juego.mesa = repartir(mazo, 1, juego.mesa);
            juego.cantidad_cartas += 1;

            for (int j = 0; j < cantidad_jugadores; j++) {

                if ((jugadores + j) -> en_ronda) {

                    (jugadores + j) -> mano =  repartir(mazo, 1, (jugadores + j) -> mano);
                    apuesta(&juego, jugadores+j);
                }                
            }
        }
        break;
    }
}
//         //Se revisa quien gano
        
//         //apuesta
    


void main () {
    
    jugar();
}