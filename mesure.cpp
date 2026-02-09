#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "sorters.hpp"
#include "mesure.hpp"

using namespace std;

void generation_aleatoire(vector<int>&D,int n){
    static mt19937 gen(random_device{}());
    uniform_int_distribution<> distribution(1,1000);
    D.clear();
    D.reserve(n);
    for (int i = 0; i < n; i++){
        int alea = distribution(gen);
        D.push_back(alea);
    }
}

void afficher_liste(vector<int>&D){
    if (D.size() == 0) cout << "List is empty !" << endl;
    cout << "Size: " << D.size() << endl;
    for (int ele : D){
        cout << ele << " ";
    }
    cout << "\n\n" << endl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Fonction de mesure et de benchmark de mes tri

double mesure(TriFn tri, const vector<int>&D){
    vector<int>d_test = D;
    auto debut = chrono::steady_clock::now();
    tri(d_test);
    auto fin = chrono::steady_clock::now();
    auto duree = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);
    return duree.count();
}

double mesure_affine(Tri func_tr,vector<int>&d){
    vector<int>temps_t(d);
    auto debut = chrono::steady_clock::now();
    func_tr.tri(temps_t);
    auto fin = chrono::steady_clock::now();
    auto duree = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut);
    cout << "Le temps de Tri de " << func_tr.nom << " est " << duree.count() << "µs" << endl;
    return duree.count();
}

void mesure_totale(vector<Tri>& trr,vector <int>&d){
    for(Tri x:trr){
        mesure_affine(x,d);
    }
}

void comparaison_sort(Tri t1,Tri t2){
    vector<int>ndc;
    generation_aleatoire(ndc,100);
    vector<int>ndc2 = ndc;
    auto tp1 = mesure(t1.tri,ndc);
    auto tp2 = mesure(t2.tri,ndc2);
    if (tp1 < tp2){
        cout << "Le tri le plus rapide est " << t1.nom << endl;
    } else {
        cout << "Le tri le plus rapide est " << t2.nom << endl;
    }
}

double mean_complexity(Tri tri_func,int n,size_t precision,bool affichage_ele){
    if (precision == 0){
        fprintf(stderr,"Precision ne peut être égale à 0");
        return 0;
    }
    vector<long long> result_tab;
    result_tab.reserve(precision);
    for (int i = 0; i < precision; i++){
        vector<int>dl;
        generation_aleatoire(dl,n);
        result_tab.push_back(mesure(tri_func.tri,dl));
    }
    if (affichage_ele == true){
        for (long long y:result_tab){
            cout << y << " \n";
        }
    }
    long long somme_result = 0;
    for (long long x : result_tab){
        somme_result += x;
    }
    long long mean_ress = (somme_result/precision);
    return mean_ress;
}

void complexity_evolution(Tri tri_funct,int mean_pres){
    vector<int> tailles = {100,500,1000,5000,7500,10000,15000};
    cout << "Evolution du Tri " << tri_funct.nom << " en moyenne sur " << mean_pres << "mesures" << endl;

    for (int taille:tailles){
        double moyenne = mean_complexity(tri_funct,taille,mean_pres,false);
        cout << "Pour " << taille << " éléments" << " on compte " << moyenne  << "µs en moyenne "<< endl;
    }
}

//Mean_press -> Précision des test pour mean_pres = 10, on va effectuer 10 teste d'affilé pour le même nombre d'élément on ferra ensuite une moyenne de cest mean_pres resultat pour avoir une complexité moyennne

void export_csv(Tri tri_funct,int mean_pres,string fichier_n){
    ofstream fichier(fichier_n);
    if(fichier.is_open()){
        fichier <<  tri_funct.nom << "," << "Précision:"<< mean_pres <<"\n";
        fichier << "Taille,Temps" << "\n";
        vector<int> tailles = {100,500,1000,5000,7500,10000,15000};
        for (int taille:tailles){
            double moyenne = mean_complexity(tri_funct,taille,mean_pres,false);
            fichier << taille << "," << moyenne << "\n";
        }
        fichier.close();
    }
    cout << "Importation SUCCESFUL" << endl;
}

void export_final_csv(vector<Tri> tr_tl,int mean_pres){
    ofstream fichier("result_final.csv");
    vector<int>tailles = {100,500,1000,2500,5000,7500,10000};
    vider_csv();
    if(fichier.is_open()){
        fichier << "Precision: "<< mean_pres << "\n";
        fichier << "Taille";
        for(const Tri& t:tr_tl){
            fichier << "," << t.nom;
        }
        fichier << endl;
        for (int taille:tailles){
            fichier << taille;
            for (const Tri& t : tr_tl){
                double moyenne = mean_complexity(t,taille,mean_pres,false);
                fichier << "," << moyenne;
            }
            fichier << "\n";
            cout << "Taille " << taille << " terminée" << endl;
        }
        fichier.close();
        cout << "Export terminé" << endl;
    }
}


bool verificationTri(Tri f_tri){
    vector<int>d1;
    generation_aleatoire(d1,100);
    vector<int>d2 = d1;
    f_tri.tri(d1);
    sort(d2.begin(),d2.end());
    if (d1 == d2){
        cout << "Le tri "<< f_tri.nom << " est opérationnel" << endl;
        return true;
    } else {
        cout << "ERREUR, le tri " << f_tri.nom << "n'est pas opérationnel" << endl;
        return false;
    }
}

void vider_csv(){
    ofstream fichier("result_final.csv",ios::trunc);
    fichier.close();
}
