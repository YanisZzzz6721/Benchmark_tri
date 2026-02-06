#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int generation_aleatoire(deque<int>&D,int n){
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

    // Test function swap
    deque<int> d = {1,3,9,12};
    afficher_liste(d);
    swap(d[1],d[3]);
    afficher_liste(d);




    selection_sort(dli);
    cout << "Resultat du tri par selection :\n" << endl;
    afficher_liste(dli);
    
    




    return 0;
}