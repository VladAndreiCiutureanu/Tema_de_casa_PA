import random
import time
#se includ modelele time si random din biblioteca standard Python 
start = time.time();#se porneste cronometrul executiei programului

class Homar:
    def __init__(self, id, dimensiune, valoare):#se defineste constructorul si se initializeaza atributele homarului
        self.id = id
        self.dimensiune = dimensiune
        self.valoare = valoare
        #self este folosit pentru a accesa variabilele clasei respective si permite fiecarei instante a clasei sa pastreze propriile date

class KMatrix:
    def __init__(self, nr_linii, nr_coloane):
        self.nr_linii = nr_linii
        self.nr_coloane = nr_coloane
        self.matrice = [0] * (nr_linii * nr_coloane)#matricea este reprezentata intern ca o lista unidimensionala

def generare_date_intrare():
    random.seed(time.time())#seed pentru generarea numarului de homari si a capacitatii maxime
    nr_homari = random.randint(1, 20000)
    capacitate_maxima = random.randint(1, 20000)#se genereaza pseudo-aleatoriu valoarea datelor de intrare
    print(f"Numar homari : {nr_homari}")#f permite introducerea expresiilor in interiorul string-ului, evaluate la runtime si folosind valorile curente ale variabilelor
    print(f"Capacitatea maxima a plasei pescarului : {capacitate_maxima}")#{} delimiteaza expresiile
    return nr_homari, capacitate_maxima

def generare_homari(nr_homari):
    random.seed(time.time())
    homari = []
    for iterator in range(1, nr_homari + 1):
        homar = Homar(iterator, random.randint(1, 30), random.randint(1, 30))#se creeaza un nou element cu date pseudo-aleatorii cu ajutorul clasei definite anterior
        homari.append(homar)#se adauga la vectorul homari noul element creat anterior
    return homari

def print_homari(homari):
    print("Homari:")
    for homar in homari:#un alt mod de a realiza o bucla for
        print(f"id: {homar.id} dimensiune: {homar.dimensiune} valoare: {homar.valoare}")

def seteaza_valoare_matrice(matrice, indice_linie, indice_coloana, valoare_noua):
    pozitie = indice_linie * matrice.nr_coloane + indice_coloana
    matrice.matrice[pozitie] = valoare_noua

def primeste_valoare_matrice(matrice, indice_linie, indice_coloana):
    pozitie = indice_linie * matrice.nr_coloane + indice_coloana
    return matrice.matrice[pozitie]

def print_matrice(matrice):
    print("\n === Matrice === \n")
    for iterator_linii in range(matrice.nr_linii):
        for iterator_coloane in range(matrice.nr_coloane):
            print(matrice.matrice[iterator_linii * matrice.nr_coloane + iterator_coloane], end=" ")#end specifica ce caracter este afisat la finalul string-ului, valoarea implicita fiind \n
        print()#afiseaza o linie noua

def maximum(val1, val2):
    return max(val1, val2)

def algoritm_knapsack(homari, nr_homari, capacitate_maxima):
    matrice = KMatrix(nr_homari + 1, capacitate_maxima + 1)

    for iterator_valoare in range(1, matrice.nr_linii):
        for iterator_dimensiune in range(1, matrice.nr_coloane):
            valoare_fara_obiect = primeste_valoare_matrice(matrice, iterator_valoare - 1, iterator_dimensiune)#valoarea din matrice calculata pentru iterator_valoare - 1 homari si dimensiunea curenta
            if homari[iterator_valoare - 1].dimensiune <= iterator_dimensiune:
                capacitate_ramasa = iterator_dimensiune - homari[iterator_valoare-1].dimensiune#capacitatea ramasa in plasa daca este adaugat homarul curent
                valoare_capacitate_ramasa_fara_obiect = primeste_valoare_matrice(matrice, iterator_valoare - 1, capacitate_ramasa)#valoarea din matrice calculata pentru iterator_valoare -1 homari si capacitatea ramasa din plasa
                valoare_cu_obiect = homari[iterator_valoare - 1].valoare + valoare_capacitate_ramasa_fara_obiect#valoarea din matrice in cazul in care homarul curent este adaugat in plasa
                valoare_maxima = maximum(valoare_cu_obiect, valoare_fara_obiect)
                seteaza_valoare_matrice(matrice, iterator_valoare, iterator_dimensiune, valoare_maxima)#se introduce in matrice valoarea convenabila
            else:
                seteaza_valoare_matrice(matrice, iterator_valoare, iterator_dimensiune, valoare_fara_obiect)

    dimensiune = capacitate_maxima
    valoare_knapsack = primeste_valoare_matrice(matrice, matrice.nr_linii - 1, matrice.nr_coloane - 1)#valoarea din plasa
    #print_matrice(matrice)#este optionala, nu se recomanda in cazul unor date mari de intrare
    print("=== Homari selectati : ")
    for iterator in range(nr_homari, 0, -1): #se afiseaza homarii selectati in plasa
        if primeste_valoare_matrice(matrice, iterator, dimensiune) != primeste_valoare_matrice(matrice, iterator - 1, dimensiune):
            print(homari[iterator-1].id, end=" ")
            dimensiune -= homari[iterator - 1].dimensiune

    print(f"\n=== Valoare in plasa {valoare_knapsack} ===")

nr_homari, capacitate_maxima = generare_date_intrare()#asignarea dubla este posibila in Python
homari = generare_homari(nr_homari)
print_homari(homari)
algoritm_knapsack(homari, nr_homari, capacitate_maxima)
end = time.time();#se opreste cronometrul executiei programului
print("Timpul de executie al programului este ", end-start, "secunde")#se determina timpul de executie al programului

