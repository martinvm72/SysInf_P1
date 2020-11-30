import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

#Variable pour définir la résolution du graphe (résolution ~=~ 300dim * 133dim)
dim = 10

#Lecture des résultats dans le CSV
results = pd.read_csv("src/CSV/T2_2.csv")["Time"]

#Réglages du graphe
plt.figure(figsize=(3*dim, (4/3)*dim))
plt.title("Tâche 2.2", fontsize=3*dim, fontweight="bold")
plt.xlabel('nombre de threads', fontsize=3*dim)
plt.ylabel('temps (secondes)', fontsize=3*dim)
plt.grid(which='both')

#Calcul du graphe
plt.plot(range(1, 17), results, color="blue", label="test and set", linewidth=dim//3)
plt.ylim(ymin = 0)
plt.legend(fontsize = 2*dim)

#Sauvegarde du graphe
plt.savefig("PlotT22", bbox_inches="tight")