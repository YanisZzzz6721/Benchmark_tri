# Benchmark de tri en C++

## Description

Ce programme compare les temps d'exécution des différentes méthodes de tri :
- les tri implémentés manuellement (insertion,selection,bubble,quick,merge)
- le tri standard `std::sort`

Le but est d'observer les différences de performances entre un algorithme naïf et un algorithme optimisé de la STL.

---

## Compilation

```bash
g++ -std=c++17 main.cpp -o benchmark