#include <stdlib.h>
#include <stdio.h>

enum bool {
    True = 1,
    False = 0
};

enum tipo_carta {
    diamantes=0,
    corazones=1,
    trebol=2,
    espadas=3
};

enum valor_carta {
    A=0,
    dos=1,
    tres=2,
    cuatro=3,
    cinco=4,
    seis=5,
    siete=6,
    ocho=7,
    nueve=8,
    diez=9,
    J=10,
    Q=11,
    K=12
};

typedef struct carta {
    int valor_carta;
    int tipo_carta;
    int eliminado;
} carta;

typedef struct mazo {
    struct carta baraja[52];
    int restantes;
} mazo;

typedef struct jugador {
    char * nombre;
    carta * mano;
    enum bool en_ronda;
    int dinero
} jugador;

typedef struct juego {
    carta *mesa;
    int apuesta_actual;
    int cantidad_cartas;
    int apuesta_minima;
    int jugadores_en_ronda;    
} juego;

mazo* crear_mazo () {
    
    int j = 0;
    mazo *nuevo_mazo = malloc(sizeof( mazo));
    int k = 0;

    for (j = 0; j<4; j++) {
        
        for (int i = 0; i<13; i++) {
             carta nueva_carta;
            
            nueva_carta.tipo_carta = j;
            nueva_carta.valor_carta = i;
            (*(nuevo_mazo)).baraja[k] = nueva_carta;
            k++;
        }
    }

    (*(nuevo_mazo)).restantes = 52;
    return nuevo_mazo;
}

carta* repartir(mazo* baraja, int cantidad) {

    if (cantidad > (*baraja).restantes) {

        return NULL;

    }

    time_t t;
    srand((unsigned) time(&t));

     carta *mano = malloc(cantidad*sizeof( carta));
    int j = 0;

    for (int i = 0 ; i < cantidad ; i++ ) {
        
         carta nueva_carta;
        int random = rand() % 52;
        
        if ( (*baraja).baraja[random].eliminado == 0) {
            i--;
            continue;
        }

        nueva_carta =  (*baraja).baraja[random];
        *(mano + j) = nueva_carta;
        j++;
         (*baraja).baraja[random].eliminado = 0;
         (*baraja).restantes --;        
   }

   return mano;
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

void imprimir_mano (carta* mano, int cantidad) {

    for (int i = 0; i<cantidad; i++) {

        imprimir_carta(*(mano + i));
        printf("   ");

    }
    printf("\n");
}

void apuesta (juego* juego, jugador* jugador, int cantidad) {

    printf("Es el turno de %s su dinero actual es: %d\n", jugador -> nombre, jugador -> dinero);

    printf("Las cartas sobre la mesa son: \n");
    imprimir_mano(juego->mesa, juego->cantidad_cartas);

    printf("Su mano es: \n");
    imprimir_mano(jugador -> mano, cantidad);

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

        else if (apuesta < juego->apuesta_minima) {
            printf(" \n\n\nLa apuesta deber ser igual o mayor que %d \n", juego->apuesta_minima);
        }
        
        else {
            juego -> apuesta_minima = apuesta;
            juego -> apuesta_actual += apuesta;

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
    jugador jugador2;
    jugador2.nombre = "yolo";
    jugador2.dinero = dinero_inicial;

    *jugadores = jugador1;
    *(jugadores + 1) = jugador2;


    while (cantidad_jugadores_eliminados != cantidad_jugadores - 1) {
        
        juego juego;
        juego.jugadores_en_ronda = cantidad_jugadores;
        mazo *mazo = crear_mazo();

        //cartas iniciales sobre la mesa
        juego.mesa = repartir(mazo, 2);
        juego.cantidad_cartas = 2;
        juego.apuesta_minima = 0;
        int cartas_jugador = 2;

        cargar_jugadores_en_ronda(jugadores, cantidad_jugadores, &juego.jugadores_en_ronda);
        //se reparte 2 cartas a cada jugador
        for (int i = 0; i < juego.jugadores_en_ronda; i++) {

            (*(jugadores + i)).mano =  repartir(mazo, 2);
            apuesta(&juego, jugadores+i, cartas_jugador);
        }

 

        // break;
        //apuesta
    }
}

void main () {
    // mazo *mazo = crear_mazo();

    // carta * mano = repartir(mazo, 5);
    // carta * mano1 = repartir(mazo, 1);

    // imprimir_mano(mano, 5);

    // if (mano1 == NULL) {
    //     printf("hola");

    // }
   
   jugar();

    // imprimir_carta(*(mano1) );
      

}