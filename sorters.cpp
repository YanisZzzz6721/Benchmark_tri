#include "sorters.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void selection_sort(vector<int>&D){
    int size = D.size();

    for (int i = size - 1; i >= 0; i--){ 
        int max_ind = 0;

        for (int j = 1; j <= i; j++){ 
            if (D[j] > D[max_ind])
                max_ind = j;
        }
        swap(D[max_ind],D[i]); 
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void insertion_sort(vector<int>&D){
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void quick_sort(vector<int>&d){
    if(d.size()<=1){
        return ;
    }
    int pivot = d.back();
    d.pop_back();

    vector<int>petit; // Allocation mémoire
    vector<int>grand; // Allocation mémoire

    for (int x:d){
        if (x < pivot) petit.insert(petit.begin(),x);
        else grand.insert(grand.begin(),x);  //O(n) à chaque insertion
    }

    quick_sort(petit);
    quick_sort(grand);

    d.clear();
    for (int x: petit) d.push_back(x); //Copie de tout les élements
    d.push_back(pivot);
    for (int x : grand) d.push_back(x); //Copie de tout les élements
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Version optimisé du quick_sort ou l'on travaille uniquement dans le même tableau original paqs de nouvelle alocation mémoire 
à chaque appel reccursif, uniquement swap donc aucune allocation.*/

void quick_sort_inplace(vector<int>&D, int debut,int fin){
    if (debut >= fin) return;
    int pivot = D[fin];
    int i = debut - 1;
    for (int j = debut; j < fin; j++){
        if (D[j] < pivot){
            i++;
            swap(D[i], D[j]);
        }
    }
    swap(D[i + 1], D[fin]);
    int pi = i + 1;
    quick_sort_inplace(D,debut,pi-1);
    quick_sort_inplace(D,pi+1,fin);
}

void quick_sort_optimise(vector<int>&d){
    if (d.size() <= 1) return;
    quick_sort_inplace(d,0,d.size()-1);
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void fusionner(vector<int>& d, int debut, int milieu, int fin){
    vector<int> temp;
    int i = debut;
    int j = milieu;
    while (i < milieu && j < fin){
        if (d[i] < d[j]){
            temp.push_back(d[i]);
            i++;
        }
        else{
            temp.push_back(d[j]);
            j++;
        }
    }
    while (i < milieu){
        temp.push_back(d[i]);
        i++;
    }
    while (j < fin){
        temp.push_back(d[j]);
        j++;
    }
    for (int k = 0; k < temp.size(); k++){
        d[debut + k] = temp[k];
    }
}

void merge_sort(vector<int>&D,int debut,int fin){
    if((fin - debut) <= 1) return;
    int milieu = (debut+fin)/2;
    merge_sort(D,debut,milieu);
    merge_sort(D,milieu,fin);
    fusionner(D,debut,milieu,fin);
}

/*On a besoin d'un wrapper pour l'appel ensuite danxs la fonction comparaison sort,pour son pointeur de fonction*/
void merge_sort_wrapper(vector<int>&D){
    if(D.empty()) return;
    merge_sort(D,0,D.size());
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void fusion_opti(vector<int>& d, vector<int>& tmp,int debut,int milieu,int fin){
    for (int k = debut; k < fin; k++){
        tmp[k] = d[k];
    }
    int i = debut, j = milieu;
    for (int k = debut; k < fin; k++){
        if (i >= milieu) d[k] = tmp[j++];
        else if (j >= fin) d[k] = tmp[i++];
        else if (tmp[i] <= tmp[j]) d[k] = tmp[i++];
        else d[k] = tmp[j++];
    }
}

void merge_sort_optimise(vector<int>& d,vector<int>& tmp,int debut,int fin){
    if((fin - debut) <= 1) return;
    int milieu = (debut + fin) / 2;
    merge_sort_optimise(d,tmp,debut,milieu);
    merge_sort_optimise(d,tmp,milieu,fin);
    fusion_opti(d,tmp,debut,milieu,fin);
}

void merge_sort_optimise_wrapper(vector<int>&d){
    if(d.empty()) return;
    vector<int> temp(d.size());
    merge_sort_optimise(d,temp,0,d.size());
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Tri à bulle

void bubble_sort(vector<int>&v){
    int end = v.size();
    while (end > 1){
        int last_point = 0;
        for (int j = 0; j < end-1; j++){
            if (v[j] > v[j+1]){
                swap(v[j],v[j+1]);
                last_point = j+1;
            }
        }
        end = last_point;
    }
}