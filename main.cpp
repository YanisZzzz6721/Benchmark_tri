#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

using TriFn = void(*)(deque<int>&);

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
        int max_ind = i;

        for (int j = 1; j <= i; j++){ // from start to end
            if (D[j] > D[max_ind])
                max_ind = j;
        }

        swap(D[max_ind],D[i]);  // swap max_val with array[i]
    }
}

long long mesure(TriFn tri, const deque<int>&D){
    deque<int>d_test = D;
    auto debut = chrono::steady_clock::now();
    tri(d_test);
    auto fin = chrono::steady_clock::now();
    auto duree = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);
    return duree.count();
}

long long mean_complexity(TriFn tri,size_t precision,bool affichage_ele){
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


int main(){
    //Initialisation de la liste aléatoire
    deque<int> dli;
    generation_aleatoire(dli,100);
    afficher_liste(dli);
    deque<int>dlc(dli);
    afficher_liste(dlc);

    //implémentation des différent algo de tri par la suite !!!
    sort(dlc.begin(),dlc.end());
    afficher_liste(dlc);
    afficher_liste(dli);


    // Selection_sort test 
    selection_sort(dli);
    cout << "Resultat du tri par selection :\n" << endl;
    afficher_liste(dli);
    
    long long tmp = mesure(selection_sort,dli);
    cout << "Temps de tri :" << tmp << endl;
    long long mean_tmp = mean_complexity(selection_sort,20,true);
    cout << "Moyenne de temps de tri :" << mean_tmp << endl;




    return 0;
}