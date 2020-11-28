import pandas as pd
import matplotlib.pyplot as plt

cores = 8
results = []

for N in range(1, 2*cores):
    results.append()



#####################################################################################
allImpl = False # Choose your mutex implementation here!!!!! False => lpthread only; True => all
probleme = 2 # Choose your probleme here!!!!! ONLY ONE
#####################################################################################

dim = 10
if allImpl:
    folders = ["lpthread", "ts", "tts", "btts"]
else:
    folders = ["lpthread"]
leg = ["lpthread", "test and set", "test and test and set", "backoff test and test and set"]
colors = ["blue", "gold", "blueviolet", "crimson"]
file = ["philosophes", "prodCons", "readerWriter"][probleme]
titles = ["Problème des philosophes", "Problème des producteurs-consommateurs", "Problème des lecteurs et écrivains"]

plt.figure(figsize=(3*dim, (4/3)*dim))


#Plot settings
plt.title("\n"+titles[probleme], fontsize=3*dim, fontweight="bold")
plt.xlabel('nombre de threads', fontsize=3*dim)
plt.ylabel('temps moyen (secondes)', fontsize=3*dim)

#read all CSV's data
for j, folder in enumerate(folders):
    data = pd.read_csv("src/CSV_AWS8/" + folder + "/" + file + ".csv")
    time = data["Time"]
    means = []
    stds = [] #Standard deviations

    for k in range(len(time)//5): #Adapt the data to an appropriate plotable format (calculate the means per time)
        raw = np.array(time[k*5:k*5+5])
        means.append(sum(raw)/5)
        stds.append(stt.stdev(raw))

    x = range(2, len(means)+2)
    plt.plot(x, means, color=colors[j], label=leg[j], linewidth=dim//3)
    markers, caps, bars = plt.errorbar(x, means, stds, fmt='none', ecolor=colors[j], lw = dim//3, capsize=dim, capthick=dim//3) #Plot the standard deviation
    #[bar.set_alpha(0.3) for bar in bars]
    plt.tick_params(labelsize = 2*dim)
plt.ylim(ymin = 0)
plt.grid(which='both')
plt.grid(which='minor', alpha=0.2, linestyle='--')
plt.legend(fontsize = 2*dim)

#plt.suptitle("\n"+titles[probleme], fontsize = 6*dim)
plt.subplots_adjust(hspace = 0.3)
plt.savefig("PlotSimple_" + file + "8", bbox_inches='tight')