#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

using TriFn = void(*)(vector<int>&);
/*Remplacement des deque par les vector car plus rapide et contigue*/

typedef struct Tri{
    string nom;
    TriFn tri;
}Tri;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


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

void selection_sort(vector<int>&D){
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
    cout << "Le temps de Tri de " << func_tr.nom << " est " << duree.count() << endl;
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
        cout << "Pour " << taille << " éléments" << " on compte " << moyenne  << " en moyenne "<< endl;
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


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