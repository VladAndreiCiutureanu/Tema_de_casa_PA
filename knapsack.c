#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "knapsack.h"
void generare_date_intrare(int *nr_homari, int *capacitate_maxima)
{
    time_t timp;
    srand((unsigned) time(&timp));//seed pentru generarea pseudo-aleatoare a datelor de intrare
    *nr_homari = rand()%20000 + 1;//generarea numarului de homari
    *capacitate_maxima = rand()%20000 + 1;//generarea capacitatii maxime a plasei pescarului
    printf("Numar homari : %d\n", *nr_homari);
    printf("Capacitatea maxima a plasei pescarului : %d\n", *capacitate_maxima);
}
void generare_homari(struct homar *homari, int nr_homari)
{
    int iterator;
    time_t timp;

    srand((unsigned) time(&timp));//seed pentru generarea pseudo-aleatoare a datelor despre fiecare homar - identificator, dimensiune si valoare
    for(iterator = 1; iterator <= nr_homari; iterator++)
    {
        homari[iterator].id = iterator;//identificatorul primeste valoare curenta a iteratorului
        homari[iterator].dimensiune = rand()%30 + 1;//generare dimensiunii homarului curent
        homari[iterator].valoare = rand()%30 + 1;//generare valorii homarului curent
    }
}

void print_homari(struct homar *homari, int nr_homari)
{
    int iterator;

    printf("Homari:");
    for (iterator = 1; iterator <= nr_homari ; iterator++)
    {
        printf("\n id: %d dimensiune: %d valoare: %d",homari[iterator].id, homari[iterator].dimensiune, homari[iterator].valoare);//se afiseaza detaliile fiecarui homar
    }
}

void seteaza_valoare_matrice(struct k_matrice matrice, int indice_linie, int indice_coloana, int valoare_noua)
{
    int pozitie;
    pozitie = indice_linie * matrice.nr_coloane + indice_coloana;
    *(matrice.matrice + pozitie) = valoare_noua;//inseram o valoare noua in matrice pe pozitia [indice_linie][indice_coloana]
}


int primeste_valoare_matrice(struct k_matrice matrice, int indice_linie, int indice_coloana)
{
    int pozitie;

    pozitie = indice_linie * matrice.nr_coloane + indice_coloana;
    return *(matrice.matrice + pozitie);//se returneaza valoarea de pe pozitia [indice_linie][indice_coloana]
}

void print_matrice(struct k_matrice matrice)
{
    int iterator_linii;
    int iterator_coloane;

    printf("\n === Matrice === \n");
    for(iterator_linii = 0; iterator_linii < matrice.nr_linii; iterator_linii++)//se afiseaza matricea
    {
        for(iterator_coloane = 0; iterator_coloane < matrice.nr_coloane; iterator_coloane++)
        {
            printf("%d ",matrice.matrice[iterator_linii * matrice.nr_coloane + iterator_coloane]);//se afiseaza valoarea de pe pozitia [indice_linie][indice_coloana]
        }
        printf("\n");
    }
}

int maximum(int val1, int val2)
{
    if (val1 > val2)
    {
        return val1;
    }
    else
    {
        return val2;
    }
}

void algoritm_knapsack(struct homar *homari, int nr_homari, int capacitate_maxima)
{
    struct k_matrice matrice;
    int valoare_knapsack;
    int iterator_valoare;
    int iterator_dimensiune;
    matrice.nr_linii = nr_homari + 1;
    matrice.nr_coloane = capacitate_maxima + 1;
    matrice.matrice = calloc((matrice.nr_linii) * (matrice.nr_coloane), sizeof(int));//prin calloc se initializeaza matricea cu 0 pe fiecare pozitie

    for(iterator_valoare=1; iterator_valoare<matrice.nr_linii; iterator_valoare++)
        for(iterator_dimensiune=1; iterator_dimensiune<matrice.nr_coloane; iterator_dimensiune++)
        {
            int valoare_fara_obiect = primeste_valoare_matrice(matrice, iterator_valoare-1, iterator_dimensiune);//valoarea din matrice calculata pentru iterator_valoare - 1 homari si dimensiunea curenta
            if(homari[iterator_valoare].dimensiune <= iterator_dimensiune)
            {
                int capacitate_ramasa = iterator_dimensiune - homari[iterator_valoare].dimensiune;//capacitatea ramasa in plasa daca este adaugat homarul curent
                int valoare_capacitate_ramasa_fara_obiect = primeste_valoare_matrice(matrice, iterator_valoare-1, capacitate_ramasa);//valoarea din matrice calculata pentru iterator_valoare -1 homari si capacitatea ramasa din plasa
                int valoare_cu_obiect = homari[iterator_valoare].valoare + valoare_capacitate_ramasa_fara_obiect;//valoarea din matrice in cazul in care homarul curent este adaugat in plasa
                int valoare_maxima = maximum(valoare_cu_obiect, valoare_fara_obiect);
                seteaza_valoare_matrice(matrice, iterator_valoare, iterator_dimensiune, valoare_maxima);//se introduce in matrice valoarea convenabila
            }
            else
                seteaza_valoare_matrice(matrice, iterator_valoare, iterator_dimensiune, valoare_fara_obiect);
        }
    int dimensiune = capacitate_maxima;
    valoare_knapsack = primeste_valoare_matrice(matrice, matrice.nr_linii - 1, matrice.nr_coloane - 1);//valoarea din plasa
    //print_matrice(matrice);//optional se poate afisa matricea; nu se recomanda in cazul unor date de intrare mari
    printf("\n=== Homari selectati : \n ");
     for(int iterator = nr_homari; iterator >= 1; iterator--)// se determina homarii selectati in plasa, parcurgandu-se de la nr_homari catre 1
    {
        if(primeste_valoare_matrice(matrice, iterator, dimensiune)!=(primeste_valoare_matrice(matrice, iterator-1, dimensiune)))//daca homarul curent a fost adaugat in plasa
            {
                printf("%d ", homari[iterator].id);//se afiseaza identificatorul homarului adaugat
                dimensiune -= homari[iterator].dimensiune;//se actualizeaza dimensiunea ramasa
            }
    }
    free(matrice.matrice);//se elibereaza zona din memorie unde a fost stocata matricea

    printf("\n=== Valoare in plasa %d ===", valoare_knapsack);//se afiseaza valoarea din plasa
}
