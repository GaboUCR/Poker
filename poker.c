#include <stdlib.h>
#include <stdio.h>
// #include "linkedList.h"
#include "poker.h"
#include <string.h>

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

void valor_de_mano (node* mano, node* mesa) {

    // comprobar straigh flush
    carta posible_flush[100];
    int j = 0;
    int cantidad_tipo = 0;



    for (int i = 0; i < 4; i++) {

        j = 0;
        cantidad_tipo = 0;

        node * actual = mano;
        
        while (actual != NULL) {

            if ( ( (actual -> carta) -> tipo_carta) == i) {

                cantidad_tipo += 1;
                posible_flush[j] = *(actual -> carta);
                j++;
                
            }
            actual = actual -> next;

        }

        actual = mesa;

        while (actual != NULL) {

            if ( ( (actual -> carta) -> tipo_carta) == i) {

                cantidad_tipo += 1;
                posible_flush[j] = *(actual -> carta);
                j++;
                
            }
            actual = actual -> next;

        }
        

        if (cantidad_tipo >= 5) {

            carta flush_ordenado[15];
            int secuencia = 1;

            while (True) {

                for (int i = 0; i < 10; i++) {
                    carta c = posible_flush[i];
                    int siguiente;

                    if (c.valor_carta == K) {
                        siguiente = A;
                    }
                    else {
                        siguiente = c.valor_carta + 1;
                    }

                    for (int j = i+1; j<10; j++) {


                        if (posible_flush[j].valor_carta == siguiente) {
                            secuencia++;
                        }
                    }

                }
            }



            
        }            

    }

    


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
        //Se revisa quien gano


        break;
    }
}
        
        
        //apuesta


void mensaje_bienvenida () {

    printf(".------..------..------..------..------..------..------..------..------..------.\n");
    printf("|B.--. ||I.--. ||E.--. ||N.--. ||V.--. ||E.--. ||N.--. ||I.--. ||D.--. ||O.--. |\n");
    printf("| :(): || (\\/) || (\\/) || :(): || :(): || (\\/) || :(): || (\\/) || :/\\: || :/\\: |\n");
    printf("| ()() || :\\/: || :\\/: || ()() || ()() || :\\/: || ()() || :\\/: || (__) || :\\/: |\n");
    printf("| '--'B|| '--'I|| '--'E|| '--'N|| '--'V|| '--'E|| '--'N|| '--'I|| '--'D|| '--'O|\n");
    printf("`------'`------'`------'`------'`------'`------'`------'`------'`------'`------'\n\n");
}

// recibe dos strings y revisa si la primera string comienza con la segunda string
int strstarts(const char *str, const char *prefix)
{
     return strncmp(str, prefix, strlen(prefix)) == 0;
}

// Recibe un entero y revisa que sea un número de base 10
int revisar_input (char* a) {

    int cantidad = strlen(a);
    int i = 0;
    char menos [] = "-";

    if (strstarts(a, menos)) {
        i++;
    }

    for (i; i <cantidad; i++) {

        if (!isdigit(*(a+i))) {
            return 0;
        }
    }

    return 1;
}




void f_main () {

    mensaje_bienvenida();

    printf("¿Que desea hacer?\n");
    printf("\n(1)   ¡Jugar!");
    printf("\n(2)   Reglas");
    printf("\n(3)   Mejores manos ");
    printf("\n(4)   Salir\n");
    printf("Elija una opción (1-4):  ");

    char opcion [1000];

    scanf("%s", opcion);

    int i = revisar_input(opcion);

    printf("%d\n" , i);
}
    


void main () {
    f_main();
    // printf("llegamos");
    // node* mano = NULL;
    // node* mesa = NULL;
    // mazo* baraja = crear_mazo();
    
    // mano = repartir(baraja, 5, mano);
    // mesa = repartir(baraja, 5, mesa);
    
    // valor_de_mano(mano, mesa);
    // jugar();

}