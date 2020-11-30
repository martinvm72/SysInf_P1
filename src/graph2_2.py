import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import statistics as stt

#Variable pour définir la résolution du graphe (résolution ~=~ 300dim * 133dim)
dim = 10

#Valeurs utiles pour différentier les graphes
leg = ["test and set", "test and test and set", "backoff test and test and set"]
colors = ["blue", "gold", "blueviolet", "crimson"]
files = ["philosophes", "prodCons", "readerWriter"]

#Lecture des résultats dans le CSV
data_ts = pd.read_csv("src/CSV/Tache2_2/ts.csv")["Time"]
data_tts = pd.read_csv("src/CSV/Tache2_2/tts.csv")["Time"]
data_btts = pd.read_csv("src/CSV/Tache2_2/btts.csv")["Time"]

#Réglages du graphe
plt.figure(figsize=(3*dim, (4/3)*dim))
plt.title("Tâche 2.2", fontsize=3*dim, fontweight="bold")
plt.xlabel('nombre de threads', fontsize=3*dim)
plt.ylabel('temps (secondes)', fontsize=3*dim)
plt.tick_params(labelsize = 2*dim)
plt.grid(which='both')
x = range(1, (len(data_ts)//5)+1)

#Calcul du graphe
for i, time in enumerate([data_ts, data_tts, data_btts]):
    means = []
    stds = [] #Déviations standards

    #Calcul des temps moyens et des déviations standards des résultats par nombre de threads
    for k in range(len(time)//5):
        raw = np.array(time[k*5:k*5+5])
        means.append(sum(raw)/5)
        stds.append(stt.stdev(raw))
    plt.plot(x, means, color=colors[i], label=leg[i], linewidth=dim//3)
    markers, caps, bars = plt.errorbar(x, means, stds, fmt='none', ecolor=colors[i], lw = dim//3, capsize=dim, capthick=dim//3) #Affiche les déviations standards
plt.tick_params(labelsize = 2*dim)
plt.legend(fontsize = 2*dim)
plt.ylim(ymin = 0)

#Sauvegarde du graphe
plt.savefig("PlotT22", bbox_inches="tight")