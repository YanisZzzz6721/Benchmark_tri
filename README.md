# Benchmark de tri en C++

## Description

Ce programme compare le temps d'exécution de deux méthodes de tri :
- un tri implémenté manuellement
- le tri standard `std::sort`

Le but est d'observer les différences de performances entre un algorithme naïf et un algorithme optimisé de la STL.

---

## Compilation

```bash
g++ -std=c++17 main.cpp -o benchmark