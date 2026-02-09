#ifndef SORTERS_HPP
#define SORTERS_HPP
#include <iostream>
#include <vector>
#include <string>

using namespace std;

using TriFn = void(*)(vector<int>&);
/*Remplacement des deque par les vector car plus rapide et contigue*/

typedef struct Tri{
    string nom;
    TriFn tri;
}Tri;

void selection_sort(vector<int>&D);

void insertion_sort(vector<int>&D);

void quick_sort(vector<int>&d);

void quick_sort_inplace(vector<int>&D, int debut,int fin);
void quick_sort_optimise(vector<int>&d);

void fusionner(vector<int>& d, int debut, int milieu, int fin);
void merge_sort(vector<int>&D,int debut,int fin);
void merge_sort_wrapper(vector<int>&D);

void fusion_opti(vector<int>& d, vector<int>& tmp,int debut,int milieu,int fin);
void merge_sort_optimise(vector<int>& d,vector<int>& tmp,int debut,int fin);
void merge_sort_optimise_wrapper(vector<int>&d);

void bubble_sort(vector<int>&v); 

#endif