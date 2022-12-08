#include <stdlib.h>
#include <stdio.h>
#include "poker.h"
#include <string.h>


void puntuacion (char * nombre, int dinero_ganado) {

    FILE* file = fopen("puntuaciones_numero.txt","r+");

    int posicion = 0;

    char nom[51];

    strcpy(nom, nombre);
    char int_anterior[51];

    for (int i =0; i<10; i++) {

        char entero[51]="";

		fread(&entero[0],1,50,file);
        
        int calificacion = atoi(entero);
        
        if (dinero_ganado > calificacion) {
            
            fseek(file ,-50, SEEK_CUR);
            
            char str1[51]="";

            int length = snprintf( NULL, 0, "%d", dinero_ganado);

            for (int i = 0; i<50-length; i++) {

                *(str1+i)= 48;
            }

            snprintf(str1+(50-length), length+1, "%d", dinero_ganado);  
                        
            fprintf(file,"%s",str1);
            
            strcpy(int_anterior, entero);

            for (int j = i+1; j<10; j++) {

                fread(&entero[0],1,50,file); 
                fseek(file ,-50, SEEK_CUR);

                fprintf(file,"%s",int_anterior);
                strcpy(int_anterior, entero);

            }


            break;
        }

        posicion++;

    }
    
	fclose(file);
 
    file = fopen("puntuaciones.txt","r+");
    fseek(file , 50*posicion, SEEK_CUR);
    char nom_anterior[51]= "";
    
    for (int i = strlen(nom); i<50; i++) {

        *(nom+i)= 32;
    }
    // printf("hola\n");
    for (int i = posicion+1; i<10; i++) {

		fread(&nom_anterior[0],1,50,file);

        fseek(file ,-50, SEEK_CUR);
        fprintf(file,"%s",nom);

        strcpy(nom, nom_anterior);
    }

    fclose(file);

}

void leer () {

    FILE *file = fopen("puntuaciones.txt","r");
    FILE* file1 = fopen("puntuaciones_numero.txt","r");

    printf("Las mejores puntuaciones son: \n \n \n");
    for (int i =0; i<10; i++) {

        char nombre[50];
        char input [51]="";

        char entero[51];
        char inputEntero[11];

		fread(&nombre[0],1,50,file);
        fread(&entero[0],1,50,file1);

        int cal = atoi(entero);

        if (cal == 0) {
            continue;
        }

        for (int i=0; i<50; i++) {

            char c = nombre[i];

            if ((c >= 97 && c <= 122) || (c>=48 && c<=57) || (c>=65 && c<=90) ) {
                input[i] = nombre[i];
                // input[i] = 0;
                
            }

            
        }

        printf("El jugador %s consiguio %d en una ronda\n\n", input, cal);

    }
    
    fclose(file);
	fclose(file1);
}