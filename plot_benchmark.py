import pandas as pd
import matplotlib.pyplot as plt

def affichage_csv_total():
    with open('result_final.csv', 'r') as f:
        premiere_ligne = f.readline().strip()
        precision = premiere_ligne.split(':')[1].strip()

    df = pd.read_csv('result_final.csv', skiprows=1)
    df.columns = df.columns.str.strip()

    plt.figure(figsize=(12, 8))
    for colonne in df.columns[1:]:
        plt.plot(df['Taille'], df[colonne], marker='o', label=colonne)
    plt.xlabel('Taille du tableau')
    plt.ylabel('Temps (µs)')
    plt.title(f'Benchmark des algorithmes de tri (Précision : {precision})')
    plt.legend()
    plt.grid(True)
    plt.yscale('log')
    plt.show()

def affichage_csv():
    with open('resultat.csv', 'r') as f:
        premiere_ligne = f.readline().strip()
        parties = premiere_ligne.split(',')
        nom_tri = parties[0]                   
        precision = parties[1].split(':')[1]    


    df = pd.read_csv('resultat.csv', skiprows=1)
    df.columns = df.columns.str.strip()


    plt.figure(figsize=(10, 6))
    plt.plot(df['Taille'], df['Temps'], marker='o')

    plt.xlabel('Taille du tableau')
    plt.ylabel('Temps (µs)')
    plt.title(f'Benchmark - {nom_tri} (Précision : {precision})')
    plt.grid(True)
    plt.yscale('log')
    plt.show()


en_marche = True
while(en_marche):
        choice = str(input("Veuillez choisir la courbe à afficher: "))
        if(choice == 'q'):
            en_marche = False
        elif choice == 'result_final.csv':
            affichage_csv_total()
            plt.close()
        elif choice == 'result.csv':
            affichage_csv()
            plt.close
        else:
            print("Mauvais choix")








