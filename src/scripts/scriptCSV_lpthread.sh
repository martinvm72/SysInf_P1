#!/bin/bash
cd output/lpthread
echo "Tests producteurs-consommateurs lpthread en cours..."
echo "Nbr threads,Time">../../src/CSV/lpthread/prodCons.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/lpthread/prodCons.csv
        /usr/bin/time -ao ../../src/CSV/lpthread/prodCons.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
    echo "Fini pour $j threads"
done
echo "Tests producteurs-consommateurs lpthread terminés"

echo "Tests philosophes lpthread en cours..."
echo "Nbr threads,Time">../../src/CSV/lpthread/philosophes.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/lpthread/philosophes.csv
        /usr/bin/time -ao ../../src/CSV/lpthread/philosophes.csv -f %e ./philo.out $j 
    done
    echo "Fini pour $j threads"
done
echo "Tests philosophes lpthread terminés"

echo "Tests lecteurs-écrivains lpthread en cours..."
echo "Nbr threads,Time">../../src/CSV/lpthread/readerWriter.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/lpthread/readerWriter.csv
        /usr/bin/time -ao ../../src/CSV/lpthread/readerWriter.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
    echo "Fini pour $j threads"
done
echo "Tests lecteurs-écriavins lpthread terminés"