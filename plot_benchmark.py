import pandas as pd
import matplotlib.pyplot as plt


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

plt.show()