#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "knapsack.h"

int main(){
    clock_t begin=clock();//se retine momentul inceperii executiei programului
    struct homar *homari;//definim vectorul de structuri homari
    int nr_homari;
    int capacitate_maxima;

    generare_date_intrare(&nr_homari,&capacitate_maxima);

    homari = malloc((nr_homari+1) * sizeof(struct homar));//alocam memorie vectorului homari
    generare_homari(homari, nr_homari);

    print_homari(homari, nr_homari);

    algoritm_knapsack(homari, nr_homari, capacitate_maxima);
    free(homari);//eliberam memoria folosita pentru vector
    clock_t end=clock();//se retine momentul sfarsirii executiei programului
    printf("\nTimpul de executie al programului este %lf secunde",(double)(end-begin)/CLOCKS_PER_SEC);//se determina timpul de executie al programului(cpu time)

    return 0;
}
