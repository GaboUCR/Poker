#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, opcion;
  char nombres[5][30];
  int apuesta[5][30]; // Aun no se ingresa la apuesta
  int jugadores;
  char *nombreArchivo = "Mejores Mano.txt";
  char *modo = "a+"; // w es para sobrescribir, a+ es para añadir al existente
  FILE *archivo = fopen(nombreArchivo, modo);

  do {

    printf("\n\n¡Bienvenido al poker! \n ¿Que desea hacer?\n\n");
    // opciones
    printf("\n(1)   ¡Jugar!");
    printf("\n(2)   Reglas");
    printf("\n(3)   Mejores manos ");
    printf("\n(4)   Salir\n");
    printf("Elija una opción (1-4):  ");

    scanf("%d", &opcion);
    switch (opcion) {
    case 1:;

      do {
        printf("\n\t\t------------POKER--------------\n\n");
        printf(
            "\n\tBienvenido Usuario a continuacion se le pedira que ingrese la "
            "cantidad y  los nombres de los jugadadores \n\n");
        printf("Ingrese la cantidad de jugadores: ");

        scanf("%d", &jugadores);
        if (jugadores != 1 && jugadores <= 5) {

          for (int i = 0; i < jugadores; i++) {
            printf("\nIngrese el nombre: ");
            scanf("%s", nombres[i]);
          }

          for (int j = 0; j < jugadores; j++) {
            printf("\n%s\n", nombres[j]);
          }
        }

        if (jugadores > 5) {
          printf("\n\nLa cantidad de jugadores supera el máximo. Recuerde que "
                 "para jugar se necesitan de 2 a 5 jugadores \n\n");
          int salida = 0;
        }
        if (jugadores == 1) {
          printf("\n\nLa cantidad de jugadores mínima es 2. Recuerde que para "
                 "jugar se necesitan de 2 a 5 jugadores \n\n");
          int salida = 0;
        }

      } while (jugadores > 5 || jugadores == 1);

      break;

    case 2:
      printf(
          "\n\nEn el siguiente enlace se pueden encontrar las reglas "
          "deljuego:https://bicyclecards.com/how-to-play/basics-of-poker\n\n");

      break;

    case 3:

      if (archivo == NULL) {
        printf("Error abriendo archivo %s", nombreArchivo);
        return 1;
      }

      fprintf(archivo, "Aquí van las mejores manos");

      fclose(archivo);
      puts("Contenido escrito correctamente");

      break;

      int opcion = 4;
    }

  } while (opcion != 4);

  return 0;
}