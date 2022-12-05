#include "poker.h"
#include <stdlib.h>
#include <stdio.h>
#include "pokerHands.h"

int comprobar_one_pair (node* mano, node* mesa) {

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

        if (cantidad_tipo >= 2) {
            return OnePair;
        }
    }
    return 0;
}

int comprobar_two_pair (node* mano, node* mesa) {

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

        if (cantidad_tipo >= 2) {

            if (!cantidad_tipo3) {
                cantidad_tipo3 = True;
            }
            else {

                cantidad_tipo2 = True;
            }
            
        }

        if (cantidad_tipo3  && cantidad_tipo2) {
            return TwoPairs;
        }
    }
    return 0;
}

int comprobar_three_of_a_kind(node* mano, node* mesa) {

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
            return ThreeOfAKind;
        }

    }

    return 0;    
}

int comprobar_straight(node* mano, node* mesa) {

    int j = 0;
    int cantidad_tipo = 0;
    carta posible_straight[100];

    node * actual = mano;
    
    while (actual != NULL) {

        posible_straight[j] = *(actual -> carta);
        j++;
            
        actual = actual -> next;

    }

    actual = mesa;

    while (actual != NULL) {

        posible_straight[j] = *(actual -> carta);
        j++;
            
        actual = actual -> next;

    }

    for (int k = 0; k <= j; k++) {

        carta c = posible_straight[k];
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

                return Straight;
            }

            int no_encontrado = 1;

            for (int w = 0; w<j; w++) {

                if (posible_straight[w].valor_carta == siguiente) {
                    
                    no_encontrado = 0;
                    secuencia++;

                    if (siguiente == K) {
                        siguiente = A;
                    }
                    else {
                        siguiente = siguiente + 1;
                    }
                    break;                           
                }
            }

            if (no_encontrado) {
                break;
            }

        }
    }
    return 0;   
}

int comprobar_flush(node* mano, node* mesa) { 

    int cantidad_tipo = 0;

    for (int i = 0; i<4; i++) {

        cantidad_tipo = 0;

        node * actual = mano;

        while (actual != NULL) {

            if ( ( (actual -> carta) -> tipo_carta) == i) {

                cantidad_tipo += 1;
                
            }
            actual = actual -> next;

        }

        actual = mesa;

        while (actual != NULL) {

            if ( ( (actual -> carta) -> tipo_carta) == i) {

                cantidad_tipo += 1;  
            }
            actual = actual -> next;

        }

        if (cantidad_tipo >= 5) {

            return Flush;
        }

    }
    return 0;
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

                            if (siguiente == K) {
                                siguiente = A;
                            }
                            else {
                                siguiente = siguiente + 1;
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

void one_pair_test () {

    node* mano = NULL;
    node* mesa = NULL;

    for (int i =0; i < 2; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = 1;
        mano = insert(c, mano);
    }

    for (int i =0; i < 1; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = i+3;
        mesa = insert(c, mesa);
    }

    printf("%d", valor_de_mano(mano, mesa));   
}

void two_pair_test () {

    node* mano = NULL;
    node* mesa = NULL;

    for (int i =0; i < 2; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = 1;
        mano = insert(c, mano);
    }

    for (int i =0; i < 2; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = K;
        mesa = insert(c, mesa);
    }

    printf("%d", valor_de_mano(mano, mesa));   
}

void three_of_a_kind_test() {

    node* mano = NULL;
    node* mesa = NULL;

    for (int i =0; i < 3; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = 1;
        mano = insert(c, mano);
    }

    
    for (int i =0; i < 1; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = K;
        mesa = insert(c, mesa);
    }

    // imprimir_mano(mano);
    // imprimir_mano(mesa);

    printf("%d", valor_de_mano(mano, mesa));
       
}

void straight_test () {

    node* mano = NULL;
    node* mesa = NULL;

    for (int i =1; i <= 3; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = i;
        mano = insert(c, mano);
    }

    for (int i = 4; i <= 5; i++) {
        carta c;
        c.tipo_carta = i;
        c.valor_carta = i;
        mesa = insert(c, mesa);
    }

    // imprimir_mano(mano);
    // imprimir_mano(mesa);

    printf("%d", valor_de_mano(mano, mesa));    
}
 
void flush_test() {

    node* mano = NULL;
    node* mesa = NULL;

    for (int i =1; i <= 3; i++) {
        carta c;
        c.tipo_carta = 0;
        c.valor_carta = i;
        mano = insert(c, mano);
    }

    for (int i = 1; i <= 2; i++) {
        carta c;
        c.tipo_carta = 0;
        c.valor_carta = i;
        mesa = insert(c, mesa);
    }

    // imprimir_mano(mano);
    // imprimir_mano(mesa);

    printf("%d", valor_de_mano(mano, mesa));       
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

void test() {
    // f_main();
    straight_flush_test();
    four_of_a_kind_test();
    full_house_test();
    flush_test();
    straight_test();
    three_of_a_kind_test();
    two_pair_test();
    one_pair_test();
}