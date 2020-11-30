#!/bin/bash
echo "Nbr threads,Time">prodCons4.csv
gcc readers_writers.c -o m -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>prodCons4.csv
        /usr/bin/time -ao prodCons4.csv -f %e ./m $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"