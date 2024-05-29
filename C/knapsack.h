#ifndef Proiect_PA
#define Proiect_PA

struct homar{
    int id;
    int dimensiune;
    int valoare;
};
//structura care contine datele despre fiecare homar
struct k_matrice{
    int nr_linii;
    int nr_coloane;
    int *matrice;
};
//structura care contine matricea prin care se rezolva problema 01 knapsack discrete
//fisierul header contine prototipul functiilor din knapsack.c, folosite ulterior in fisierul main
void generare_homari(struct homar *homari, int nr_homari);
void print_homari(struct homar *homari, int nr_homari);
void seteaza_valoare_matrice(struct k_matrice matrice, int indice_linie, int indice_coloana, int valoare_noua);
int primeste_valoare_matrice(struct k_matrice matrice, int indice_linie, int indice_coloana);
void print_matrice(struct k_matrice matrice);
int maximum(int val1, int val2);
void algoritm_knapsack(struct homar *homari, int nr_homari, int capacitate_maxima);
void generare_date_intrare(int *nr_homari, int *capacitate_maxima);

#endif //Proiect_PA
