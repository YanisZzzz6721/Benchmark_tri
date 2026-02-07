#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

using TriFn = void(*)(deque<int>&);

typedef struct Tri{
    string nom;
    TriFn tri;
}Tri;


void generation_aleatoire(deque<int>&D,int n){
    static mt19937 gen(random_device{}());
    uniform_int_distribution<> distribution(1,1000);

    for (int i = 0; i < n; i++){
        int alea = distribution(gen);
        D.push_front(alea);
    }
}

void afficher_liste(deque<int>&D){
    if (D.size() == 0) cout << "List is empty !" << endl;
    cout << "Size: " << D.size() << endl;
    for (int ele : D){
        cout << ele << " ";
    }
    cout << "\n\n" << endl;
}

void selection_sort(deque<int>&D){
    int size = D.size();

    for (int i = size - 1; i >= 0; i--){ // from end to start
        int max_ind = 0;

        for (int j = 1; j <= i; j++){ // from start to end
            if (D[j] > D[max_ind])
                max_ind = j;
        }
        swap(D[max_ind],D[i]);  // swap max_val with array[i]
    }
}

void insertion_sort(deque<int>&D){
    size_t size = D.size();
    for (int i = 1; i < size; i++){
        int cle = D[i];
        int j = i - 1;
        while (j >= 0 && D[j] > cle){
            D[j+1] = D[j];
            j--;
        }
        D[j+1] = cle;
    }
}

double mesure(TriFn tri, const deque<int>&D){
    deque<int>d_test = D;
    auto debut = chrono::steady_clock::now();
    tri(d_test);
    auto fin = chrono::steady_clock::now();
    auto duree = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);
    return duree.count();
}

void comparaison_sort(Tri t1,Tri t2){
    deque<int>ndc;
    generation_aleatoire(ndc,100);
    deque<int>ndc2 = ndc;
    auto tp1 = mesure(t1.tri,ndc);
    auto tp2 = mesure(t2.tri,ndc2);
    if (tp1 < tp2){
        cout << "Le tri le plus rapide est " << t1.nom << endl;
    } else {
        cout << "Le tri le plus rapide est " << t2.nom << endl;
    }
}

double mean_complexity(TriFn tri,size_t precision,bool affichage_ele){
    if (precision == 0){
        fprintf(stderr,"Precision ne peut être égale à 0");
        return 0;
    }
    vector<long long> result_tab;
    result_tab.reserve(precision);
    for (int i = 0; i < precision; i++){
        deque<int>dl;
        generation_aleatoire(dl,100);
        result_tab.push_back(mesure(tri,dl));
    }

    if (affichage_ele == true){
        for (long long y:result_tab){
            cout << y << " \n";
        }
    }
    long long somme_result = 0;
    for (long long x:result_tab){
        somme_result += x;
    }

    long long mean_ress = (somme_result/precision);
    return mean_ress;
}

bool verificationTri(Tri f_tri){
    deque<int>d1;
    generation_aleatoire(d1,100);
    deque<int>d2 = d1;
    f_tri.tri(d1);
    sort(d2.begin(),d2.end());
    if (d1 == d2){
        cout << "Le tri est opérationnel" << endl;
        return true;
    } else {
        cout << "ERREUR, le tri " << f_tri.nom << "est opérationnel" << endl;
        return false;
    }
}


int main(){

    //Initialisation de la liste aléatoire
    deque<int> dli;
    generation_aleatoire(dli,100);
    afficher_liste(dli);
    deque<int>dlc(dli);
    afficher_liste(dlc);

    //implémentation des différent algo de tri par la suite !!!
    afficher_liste(dlc);
    afficher_liste(dli);


    Tri selection = {"Selection",selection_sort};
    Tri insertion = {"Insertion",insertion_sort};


    double tmp = mesure(selection_sort,dli);
    cout << "Temps de tri :" << tmp << endl;
    double mean_tmp = mean_complexity(selection_sort,50,false);
    cout << "Moyenne de temps de tri :" << mean_tmp << endl;
    printf("\n");

    double tmp2 = mesure(insertion_sort,dlc);
    cout << "Temps de tri :" << tmp2 << endl;
    double mean_tmp2 = mean_complexity(insertion_sort,50,false);
    cout << "Moyenne de temps de tri :" << mean_tmp2 << endl;
    printf("\n");

    comparaison_sort(selection,insertion);
    verificationTri(selection);
    verificationTri(insertion);




    return 0;
}