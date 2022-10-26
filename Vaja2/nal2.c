#include <stdio.h>
#include <stdlib.h>
#include  <time.h>

int main() {
    srand(time(NULL));
    printf("Ugani število med 1 in 30\n");
    int stevilo = rand() % 30 + 1;
    int u;
    int steviloPoskusov = 5;
    do {
        printf("Vnesi število: ");
        scanf("%d", &u);
        if( u == stevilo) {
            printf("Uganili ste!\n");
            return 0;
        }
        if(u < stevilo){
            printf("Vnesli ste premajhno število.\n");
        }
        if(u > stevilo){
            printf("Vnesli ste preveliko število.\n");
        }
        steviloPoskusov = steviloPoskusov - 1;
        printf("Na voljo je še %d poskusov.\n", steviloPoskusov);
    } while(steviloPoskusov > 0);
    printf("Števila niste uganili. Pravilno število je bilo %d.", stevilo);
    return 0;
}
