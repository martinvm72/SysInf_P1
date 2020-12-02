#!/bin/bash
cd output/test_and_set
echo "Tests producteurs-consommateurs tets_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/ts/prodCons.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/prodCons.csv
        /usr/bin/time -ao ../../src/CSV/ts/prodCons.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
    echo "Fini pour $j threads"
done
echo "Tests producteurs-consommateurs tets_and_set terminés"

echo "Tests philosophes tets_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/ts/philosophes.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/philosophes.csv
        /usr/bin/time -ao ../../src/CSV/ts/philosophes.csv -f %e ./philo.out $j 
    done
    echo "Fini pour $j threads"
done
echo "Tests philosophes tets_and_set terminés"

echo "Tests lecteurs-écrivains tets_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/ts/readerWriter.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/readerWriter.csv
        /usr/bin/time -ao ../../src/CSV/ts/readerWriter.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
    echo "Fini pour $j threads"
done
echo "Tests lecteurs-écriavins tets_and_set terminés"