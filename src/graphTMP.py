import matplotlib.pyplot as plt

fig, ploty = plt.subplots(nrows=1, ncols=1, figsize=(100, 40))

print("nb,     mid,      end")
with open("output/lpthread/dahtah.txt", "r") as file:
    for i, line in enumerate(file):
        data = []
        #for j in line[:-1]:
            #data.append(2*(i//5) +2*i + int(j))
        elems = line.split()
        print((i//5) +2, "threads: ", (int(elems[1])-int(elems[0]))//100000, " | ", (int(elems[2])-int(elems[0]))//100000)
        #ploty.plot(range(len(data)), data)

    print("oui")
    plt.savefig("graphTMP")
    print("oui")