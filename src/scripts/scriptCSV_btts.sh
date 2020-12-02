#!/bin/bash
cd output/backoff_test_and_test_and_set
echo "Tests producteurs-consommateurs backoff_test_and_test_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/btts/prodCons.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/btts/prodCons.csv
        /usr/bin/time -ao ../../src/CSV/btts/prodCons.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
    echo "Fini pour $j threads"
done
echo "Tests producteurs-consommateurs backoff_test_and_test_and_set terminés"


echo "Tests philosophes backoff_test_and_test_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/btts/philosophes.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/btts/philosophes.csv
        /usr/bin/time -ao ../../src/CSV/btts/philosophes.csv -f %e ./philo.out $j 
    done
    echo "Fini pour $j threads"
done
echo "Tests philosophes backoff_test_and_test_and_set terminés"


echo "Tests lecteurs-écrivains backoff_test_and_test_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/btts/readerWriter.csv
for j in $(seq 2 $1);do
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/btts/readerWriter.csv
        /usr/bin/time -ao ../../src/CSV/btts/readerWriter.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
    echo "Fini pour $j threads"
done
echo "Tests lecteurs-écriavins backoff_test_and_test_and_set terminés"