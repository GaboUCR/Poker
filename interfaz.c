#include <stdlib.h>
#include <stdio.h>
// #include "linkedList.h"
#include "poker.h"
#include <string.h>
#include "interfaz.h"
 
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

jugador* pedir_nombres (int cantidad_de_jugadores) {
    
    jugador* jugadores = malloc(cantidad_de_jugadores*sizeof(jugador));

    char nombre[51];
    
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
        (jugadores+i)->nombre = malloc(51);
        strcpy((jugadores+i)->nombre, nombre);


    }

    return jugadores;

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

void mensaje_bienvenida () {

    printf(".------..------..------..------..------..------..------..------..------..------.\n");
    printf("|B.--. ||I.--. ||E.--. ||N.--. ||V.--. ||E.--. ||N.--. ||I.--. ||D.--. ||O.--. |\n");
    printf("| :(): || (\\/) || (\\/) || :(): || :(): || (\\/) || :(): || (\\/) || :/\\: || :/\\: |\n");
    printf("| ()() || :\\/: || :\\/: || ()() || ()() || :\\/: || ()() || :\\/: || (__) || :\\/: |\n");
    printf("| '--'B|| '--'I|| '--'E|| '--'N|| '--'V|| '--'E|| '--'N|| '--'I|| '--'D|| '--'O|\n");
    printf("`------'`------'`------'`------'`------'`------'`------'`------'`------'`------'\n\n");
}
