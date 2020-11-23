import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import statistics as stt

philo = pd.read_csv("CSV/lpthread/philosophes.csv")
prodCons = pd.read_csv("CSV/lpthread/prodCons.csv")
readWrite = pd.read_csv("CSV/lpthread/readerWriter.csv")

def recurMax(l):
    rep = 0
    for elem in l:
        rep = max(rep, max(elem))
    return rep

data = [philo, prodCons, readWrite]
titles = ["Problème des philosophes", "Problème des producteurs-consommateurs", "Problème des lecteurs et écrivains"]
fig, (ax1, ax2, ax3) = plt.subplots(nrows=3, ncols=1, figsize=(12, 21))
plots = [ax1, ax2, ax3]
for i in range(3):
    time = data[i]["Time"]
    y = []
    means = []
    stds = [] #Standard deviations

    for j in range(len(time)//5):
        raw = np.array(time[j*5:j*5+5])
        y.append(raw)
        means.append(sum(raw)/5)
        stds.append(stt.stdev(raw))

    x = range(2, len(y)+2)
    plots[i].set_title(titles[i])
    plots[i].grid(True)
    plots[i].set_xlabel('nbr de threads')
    plots[i].set_ylabel('secondes')
    plots[i].set_ylim([0.0, 1.2*recurMax(y)])
    plots[i].plot(x, means)
    plots[i].errorbar(x, means, stds, fmt='none', ecolor="black", lw=2)
plt.savefig("Plots")
