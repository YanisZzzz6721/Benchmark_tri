#ifndef MESURE_HPP
#define MESURE_HPP
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "sorters.hpp"

using namespace std;

void generation_aleatoire(vector<int>&D,int n);

void afficher_liste(vector<int>&D);

double mesure(TriFn tri, const vector<int>&D);
double mesure_affine(Tri func_tr,vector<int>&d);
void mesure_totale(vector<Tri>& trr,vector <int>&d);

void comparaison_sort(Tri t1,Tri t2);

double mean_complexity(Tri tri_func,int n,size_t precision,bool affichage_ele);
void complexity_evolution(Tri tri_funct,int mean_pres);

void export_csv(Tri tri_funct,int mean_pres,string fichier_n);
void export_final_csv(vector<Tri> tr_tl,int mean_pres);

bool verificationTri(Tri f_tri);

#endif