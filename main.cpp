#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "sorters.hpp"
#include "mesure.hpp"

using namespace std;

int main(){
    
    // Structure de mes tri
    Tri selection = {"Selection",selection_sort};
    Tri insertion = {"Insertion",insertion_sort};
    Tri fusion = {"Fusion",merge_sort_wrapper};
    Tri fusion_opt = {"Fusion_optimisé",merge_sort_optimise_wrapper};
    Tri rapide = {"Rapide",quick_sort};
    Tri rapide_opt = {"Rapide_optimisé",quick_sort_optimise};
    Tri bulle = {"Bulle",bubble_sort};

    vector<Tri> tr = {selection,insertion,fusion,fusion_opt,rapide,rapide_opt,bulle};
    //Verification des tris
    for (Tri x:tr){
        verificationTri(x);
    }

    //Test performance des tri
    vector<TriFn> tri_function = {selection_sort,insertion_sort,merge_sort_wrapper,merge_sort_optimise_wrapper,quick_sort,quick_sort_optimise};
    vector<int> liste;
    generation_aleatoire(liste,10000);
    mesure_totale(tr,liste);


    //Test evolution
    vector<int>v1;
    complexity_evolution(rapide_opt,10);

    export_csv(insertion,10,"resultat.csv");
    export_final_csv(tr,10);




    return 0;
}