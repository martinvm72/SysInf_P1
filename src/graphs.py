import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

philo = pd.read_csv("philosophes.csv")
prodCons = pd.read_csv("prodCons.csv")
readWrite = pd.read_csv("readerWriter.csv")

def recurMax(l):
    rep = 0
    for elem in l:
        rep = max(rep, max(elem))
    return rep

data = [philo, prodCons, readWrite]
fig, (ax1, ax2, ax3) = plt.subplots(nrows=3, ncols=1, figsize=(9, 12))
plots = [ax1, ax2, ax3]
for i in range(3):
    time = data[i][" Time"]
    y = []
    means = []
    for j in range(len(time)//5):
        raw = time[j*5:j*5+5]
        y.append(raw)
        means.append(sum(raw)/5)
    plots[i].set_ylim([0.0, 1.2*recurMax(y)])
    print(len(means))
    plots[i].violinplot(np.transpose(np.array(y)), showmeans=True)
    plots[i].plot(range(1, len(y)+1), means)
    plots[i].scatter(range(1,len(y)+1), means, marker='o', color='red')
plt.savefig("Plots")