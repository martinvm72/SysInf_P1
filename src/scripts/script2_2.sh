#!/bin/bash
cd output/T22
echo "Nbr threads,Time">../../src/CSV/Tache2_2/ts.csv
for i in $(seq 1 16);do
    echo -n "$i,">>../../src/CSV/Tache2_2/ts.csv
    /usr/bin/time -ao ../../src/CSV/Tache2_2/ts.csv -f %e ./ts.out $(($i))
done
echo "Tache 2.2 done"

echo "Nbr threads,Time">../../src/CSV/Tache2_2/tts.csv
for i in $(seq 1 16);do
    echo -n "$i,">>../../src/CSV/Tache2_2/tts.csv
    /usr/bin/time -ao ../../src/CSV/Tache2_2/tts.csv -f %e ./tts.out $(($i))
done
echo "Tache 2.2 done"

echo "Nbr threads,Time">../../src/CSV/Tache2_2/btts.csv
for i in $(seq 1 16);do
    echo -n "$i,">>../../src/CSV/Tache2_2/btts.csv
    /usr/bin/time -ao ../../src/CSV/Tache2_2/btts.csv -f %e ./btts.out $(($i))
done
echo "Tache 2.2 done"