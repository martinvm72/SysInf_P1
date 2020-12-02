import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import statistics as stt

#Variable pour définir la résolution du graphe (résolution ~=~ 300dim * 133dim)
dim = 10

#Valeurs utiles pour différentier les graphes
folders = ["lpthread", "ts", "tts", "btts"]
leg = ["lpthread", "test and set", "test and test and set", "backoff test and test and set"]
colors = ["blue", "gold", "blueviolet", "crimson"]
files = ["philosophes", "prodCons", "readerWriter"]
titles = ["Problème des philosophes", "Problème des producteurs-consommateurs", "Problème des lecteurs et écrivains"]

#Création des graphes
fig, (ax1, ax2, ax3) = plt.subplots(nrows=3, ncols=1, figsize=(3*dim, 4*dim))
plots = [ax1, ax2, ax3]


for i, file in enumerate(files):
    #Paramètres du graphe
    plots[i].set_title("\n"+titles[i], fontsize=3*dim, fontweight="bold")
    plots[i].set_xlabel('nombre de threads', fontsize=3*dim)
    plots[i].set_ylabel('temps moyen (secondes)', fontsize=3*dim)
    plots[i].grid(which='both')

    #Lecture des résultats dans les CSV
    for j, folder in enumerate(folders):
        data = pd.read_csv("src/CSV/" + folder + "/" + file + ".csv")
        time = data["Time"]
        means = []
        stds = [] #Déviations standards

        #Calcul des temps moyens et des déviations standards des résultats par nombre de threads
        for k in range(len(time)//5):
            raw = np.array(time[k*5:k*5+5])
            means.append(sum(raw)/5)
            stds.append(stt.stdev(raw))

        #Calcul et dessin du graphe
        x = range(2, len(means)+2)
        plots[i].plot(x, means, color=colors[j], label=leg[j], linewidth=dim//3)
        markers, caps, bars = plots[i].errorbar(x, means, stds, fmt='none', ecolor=colors[j], lw = dim//3, capsize=dim, capthick=dim//3) #Affiche les déviations standards
        plots[i].tick_params(labelsize = 2*dim)
    plots[i].set_ylim(ymin = 0)
    plots[i].legend(fontsize = 2*dim)

#Style global des graphes
plt.suptitle("Évaluation des performances", fontsize = 6*dim)
plt.subplots_adjust(hspace = 0.3)

#Sauvegarde des graphes
plt.savefig("Plots", bbox_inches="tight")