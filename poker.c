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
            printf(" \n\n\nLa apuesta deber ser igual o mayor que %d \n", juego->apuesta_minima);
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

int comprobar_full_house(node* mano, node* mesa) {

    int cantidad_tipo2 = 0;
    int cantidad_tipo3 = 0;
    int cantidad_tipo = 0;

    for (int i = 1; i<=13; i++) {

        cantidad_tipo = 0;

        node * actual = mano;

        while (actual != NULL) {

            if ( ( (actual -> carta) -> valor_carta) == i) {

                cantidad_tipo += 1;
                
            }
            actual = actual -> next;

        }

        actual = mesa;

        while (actual != NULL) {

            if ( ( (actual -> carta) -> valor_carta) == i) {

                cantidad_tipo += 1;  
            }
            actual = actual -> next;

        }

        if (cantidad_tipo >= 3) {

            if (!cantidad_tipo3) {
                cantidad_tipo3 = True;
            }
            else {

                cantidad_tipo2 = True;
            }
            
        }

        else if (cantidad_tipo == 2) {
            cantidad_tipo2 = True;
        }

        if (cantidad_tipo3  && cantidad_tipo2) {
            return FullHouse;
        }
    }
    return 0;
}

int comprobar_four_of_a_kind(node* mano, node* mesa) {

    int cantidad_tipo = 0;

    for (int i = 1; i<=13; i++) {
        
        cantidad_tipo = 0;
        node * actual = mano;

        while (actual != NULL) {

            if ( ( (actual -> carta) -> valor_carta) == i) {

                cantidad_tipo += 1;
                
            }
            actual = actual -> next;

        }

        actual = mesa;

        while (actual != NULL) {

            if ( ( (actual -> carta) -> valor_carta) == i) {

                cantidad_tipo += 1;  
            }
            actual = actual -> next;

        }

        if (cantidad_tipo >= 4) {
            return FourOfAKind;
        }

    }

    return 0;

}

int comprobar_straight_flush (node* mano, node* mesa) {
    int cantidad_tipo = 0;
    carta posible_flush[100];
    int j = 0;

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

            for (int k = 0; k < 10; k++) {

                carta c = posible_flush[k];
                int siguiente;
                int secuencia = 1;

                if (c.valor_carta == K) {
                    siguiente = A;
                }
                else {
                    siguiente = c.valor_carta + 1;
                }
            
                while (True) {
                    
                    if (secuencia == 5) {

                        return StraightFlush;
                    }

                    int no_encontrado = 1;

                    for (int w = 0; w<j; w++) {

                        if (posible_flush[w].valor_carta == siguiente) {
                            
                            no_encontrado = 0;
                            secuencia++;

                            if (c.valor_carta == K) {
                                siguiente = A;
                            }
                            else {
                                siguiente = c.valor_carta + 1;
                            }
                            break;                           
                        }
                    }

                    if (no_encontrado) {
                        break;
                    }

                }
            }
            
        }            

    }
    return 0;
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


    return 0;

    
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

        //se limpian todas las variables


        break;
    }
}
        
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

//pide al usuario un valor entero, si el usuario entra otro caracter lo vuelve a pedir hasta tener un entero
int pedir_input () {

    char menos [] = "-";

    while (1) {

        char opcion [1000];
        
        scanf("%s", opcion);

        if (revisar_input(opcion) == 1) {

            if (strstarts(opcion, menos)) {
                return -atoi(opcion+1);
            }

            return atoi(opcion);
        }

        printf("Input incorrecto, se espera un valor entero\n");
    }
}

int pedir_dinero_inicial () {

    printf("Ingrese el dinero inicial para cada jugador \n");
    int dinero_inicial = pedir_input();

    while (dinero_inicial <= 0) {

        printf("El dinero inicial debe ser positivo\n");    
        dinero_inicial = pedir_input();
    }

    return dinero_inicial;
}

int pedir_cantidad_de_jugadores () {

    printf("Ingrese la cantidad de jugadores \n");
    int cantidad_de_jugadores = pedir_input();

    while (cantidad_de_jugadores < 2 || cantidad_de_jugadores > 5) {

        printf("La cantidad de jugadores debe ser entre 2 y cinco \n");    
        cantidad_de_jugadores = pedir_input();
    }

    return cantidad_de_jugadores;
}

jugador* pedir_nombres (int cantidad_de_jugadores) {
    
    jugador* jugadores = malloc(cantidad_de_jugadores*sizeof(jugador));

    char nombre[100];
    

    for (int i = 0; i < cantidad_de_jugadores; i++) {

        int b = 1;

        while (b) {

            b = 0;
            
            printf("Ingrese el nombre del jugador numero %d\n\n", i+1);
            scanf("%s", nombre);

            for (int j=0; j<i; j++) {

                if (strcmp((jugadores+j) -> nombre, nombre) == 0) {
                    printf("Ya existe un jugador con el nombre %s\n\n", nombre);
                    b=1;
                }
            }
        }
        (jugadores+i)->nombre = malloc(100);
        strcpy((jugadores+i)->nombre, nombre);


    }

    return jugadores;

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
    // f_main();
    four_of_a_kind_test();
    straight_flush_test();
    full_house_test();
}

void full_house_test () {
    node* mano = NULL;
    node* mesa = NULL;

    for (int i =0; i < 3; i++) {
        carta c;
        c.tipo_carta = 3;
        c.valor_carta = 1;
        mano = insert(c, mano);
    }

    for (int i =0; i < 2; i++) {
        carta c;
        c.tipo_carta = 4;
        c.valor_carta = K;
        mesa = insert(c, mesa);
    }

    printf("%d", valor_de_mano(mano, mesa));   
}

void four_of_a_kind_test () {

    node* mano = NULL;
    node* mesa = NULL;

    for (int i =0; i < 4; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = 1;
        mano = insert(c, mano);
    }

    
    for (int i =0; i < 4; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = K;
        mesa = insert(c, mesa);
    }

    printf("%d", valor_de_mano(mano, mesa));
   
}

void straight_flush_test () {

    // f_main();
    node* mano = NULL;
    node* mesa = NULL;

    for (int i =1; i < 6; i++) {
        carta c;
        c.tipo_carta = 0;
        c.valor_carta = i;
        mano = insert(c, mano);
    }

    
    for (int i =1; i < 6; i++) {
        carta c;
        c.tipo_carta = 0;
        c.valor_carta = i;
        mesa = insert(c, mesa);
    }

    printf("%d", valor_de_mano(mano, mesa));


}