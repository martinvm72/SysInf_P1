import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import statistics as stt

dim = 10
folders = ["lpthread", "ts", "tts", "btts"]
leg = ["lpthread", "test and set", "test and test and set", "backoff test and test and set"]
colors = ["blue", "gold", "blueviolet", "crimson"]
files = ["philosophes", "prodCons", "readerWriter"]
titles = ["Problème des philosophes", "Problème des producteurs-consommateurs", "Problème des lecteurs et écrivains"]

fig, (ax1, ax2, ax3) = plt.subplots(nrows=3, ncols=1, figsize=(3*dim, 4*dim))
plots = [ax1, ax2, ax3]





for i, file in enumerate(files):
    #Plot settings
    plots[i].set_title("\n"+titles[i], fontsize=3*dim, fontweight="bold")
    plots[i].set_xlabel('nombre de threads', fontsize=3*dim)
    plots[i].set_ylabel('temps moyen (secondes)', fontsize=3*dim)

    #read all CSV's data
    for j, folder in enumerate(folders):
        data = pd.read_csv("src/CSV/" + folder + "/" + file + ".csv")
        time = data["Time"]
        means = []
        stds = [] #Standard deviations

        for k in range(len(time)//5): #Adapt the data to an appropriate plotable format (calculate the means per time)
            raw = np.array(time[k*5:k*5+5])
            means.append(sum(raw)/5)
            stds.append(stt.stdev(raw))

        x = range(2, len(means)+2)
        plots[i].plot(x, means, color=colors[j], label=leg[j], linewidth=dim//3)
        markers, caps, bars = plots[i].errorbar(x, means, stds, fmt='none', ecolor=colors[j], lw = dim//3, capsize=dim, capthick=dim//3) #Plot the standard deviation
        #[bar.set_alpha(0.3) for bar in bars]
        plots[i].tick_params(labelsize = 2*dim)
    plots[i].set_ylim(ymin = 0)
    plots[i].grid(which='both')
    plots[i].grid(which='minor', alpha=0.2, linestyle='--')
    plots[i].legend(fontsize = 2*dim)

plt.suptitle("Évaluation des performances", fontsize = 6*dim)
plt.subplots_adjust(hspace = 0.3)
plt.savefig("Plots", bbox_inches='tight')