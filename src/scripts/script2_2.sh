#!/bin/bash
cd output
echo "Nbr threads,Time">../src/CSV/T2_2.csv
for i in $(seq 1 16);do
    echo -n "$i,">>../src/CSV/T2_2.csv
    /usr/bin/time -ao ../src/CSV/T2_2.csv -f %e ./T2_2.out $(($i))
done
echo "Tache 2.2 done"