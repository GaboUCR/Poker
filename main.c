#include <stdlib.h>
#include <stdio.h>

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

// const enum tipo_carta diamantes;
// const enum tipo_carta corazones;
// const enum tipo_carta flores;
// const enum tipo_carta espadas;

typedef struct carta {
    int valor_carta;
    int tipo_carta;
    int eliminado;
} carta;

typedef struct mazo {
    struct carta baraja[52];
    int restantes;
} mazo;


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

carta* repartir( mazo* baraja, int cantidad) {

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

void main () {
     mazo *mazo = crear_mazo();

    carta * mano = repartir(mazo, 5);
    carta * mano1 = repartir(mazo, 1);

    imprimir_mano(mano, 5);

    if (mano1 == NULL) {
        printf("hola");

    }
   

    // imprimir_carta(*(mano1) );
      

}