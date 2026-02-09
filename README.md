# Benchmark des Algorithmes de Tri

Projet d'analyse comparative des performances de differents algorithmes de tri implementes en C++.

---

## Description

Ce projet permet de :
- Implementer et comparer plusieurs algorithmes de tri
- Mesurer les performances avec une precision configurable
- Exporter les resultats en CSV
- Visualiser les courbes de complexite avec Python/Matplotlib

---

## Structure du projet

```
Benchmark_tri/
├── main.cpp              # Point d'entree du programme
├── sorters.hpp           # Declarations des algorithmes de tri
├── sorters.cpp           # Implementations des algorithmes de tri
├── mesure.hpp            # Declarations des fonctions de mesure
├── mesure.cpp            # Implementations des fonctions de mesure
├── makefile              # Compilation du projet
├── plot_benchmark.py     # Script de visualisation Python
├── resultat.csv          # Export d'un seul tri
├── result_final.csv      # Export de tous les tris
├── venv/                 # Environnement virtuel Python
└── README.md             # Ce fichier
```

---

## Algorithmes implementes

| Algorithme | Complexite moyenne | Complexite pire cas | Stable |
|------------|-------------------|---------------------|--------|
| Selection Sort | O(n^2) | O(n^2) | Non |
| Insertion Sort | O(n^2) | O(n^2) | Oui |
| Bubble Sort | O(n^2) | O(n^2) | Oui |
| Quick Sort | O(n log n) | O(n^2) | Non |
| Quick Sort Optimise | O(n log n) | O(n^2) | Non |
| Merge Sort | O(n log n) | O(n log n) | Oui |
| Merge Sort Optimise | O(n log n) | O(n log n) | Oui |

### Versions optimisees

Les versions optimisees utilisent :
- Tri in-place : Pas de creation de nouveaux tableaux
- Meilleure localite memoire : Utilisation efficace du cache CPU
- Moins d'allocations : Reutilisation des buffers

---

## Prerequis

### C++
- Compilateur g++ avec support C++17
- Make

### Python (pour la visualisation)
- Python 3.x
- pandas
- matplotlib

---

## Installation

### 1. Cloner le projet

```bash
git clone https://github.com/VOTRE_USERNAME/Benchmark_tri.git
cd Benchmark_tri
```

### 2. Compiler le projet

```bash
make
```

### 3. Configurer l'environnement Python

```bash
python3 -m venv venv
source venv/bin/activate
pip install pandas matplotlib
```

---

## Utilisation

### Executer le benchmark

```bash
./main
```

### Visualiser les resultats

```bash
source venv/bin/activate
python plot_benchmark.py
```

### Options du menu Python

```
=== Menu ===
1. Afficher tous les tris (result_final.csv)
2. Afficher un seul tri (resultat.csv)
q. Quitter
```

### Nettoyer le projet

```bash
make clean
```

---

## Fonctionnalites de mesure

### Mesure simple

```cpp
double temps = mesure(selection_sort, vecteur);
```

### Moyenne sur plusieurs mesures

```cpp
double moyenne = mean_complexity(tri, taille, precision, affichage);
```

| Parametre | Description |
|-----------|-------------|
| tri | Structure Tri contenant le nom et la fonction |
| taille | Nombre d'elements a trier |
| precision | Nombre de mesures pour la moyenne |
| affichage | Afficher les details (true/false) |

### Export CSV

```cpp
// Exporter un seul tri
export_csv(tri, precision, "resultat.csv");

// Exporter tous les tris
export_final_csv(vector_de_tris, precision);
```

---

## Exemple de resultats

```
Precision: 10
Taille,Selection,Insertion,Fusion_optimise,Rapide_optimise,Bulle
100,25,15,17,8,49
500,585,351,106,58,1168
1000,2166,1416,233,128,4906
5000,51650,33528,1403,779,136492
10000,223584,135475,2976,1626,572531
```

### Observations

- Quick Sort Optimise et Merge Sort Optimise sont environ 100x plus rapides que les tris O(n^2)
- Insertion Sort est plus rapide que Selection Sort grace a l'arret anticipe
- Bubble Sort est le plus lent des tris O(n^2)

---

## Verification des tris

Chaque algorithme est teste automatiquement :

```cpp
verificationTri(selection);  // Affiche "Le tri est operationnel" ou "ERREUR"
```

---

## Fichiers CSV generes

### resultat.csv (un seul tri)

```csv
Insertion,Precision:10
Taille,Temps
100,15
500,359
1000,1403
5000,33550
7500,75197
10000,149034
15000,302138
```

### result_final.csv (tous les tris)

```csv
Precision: 10
Taille,Selection,Insertion,Fusion_optimise,Rapide_optimise,Bulle
100,25,15,17,8,49
500,585,351,106,58,1168
```

---

## Ameliorations possibles

- Ajouter Heap Sort
- Ajouter Counting Sort / Radix Sort
- Tester sur des listes deja triees / inversees
- Ajouter des tests unitaires
- Multithreading pour Merge Sort
- Interface graphique

---

## Auteur

Zouggagh

---
