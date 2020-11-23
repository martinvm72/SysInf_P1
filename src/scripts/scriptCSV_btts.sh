#!/bin/bash
cd output/backoff_test_and_test_and_set
echo "Nbr threads,Time">../../src/CSV/btts/prodCons.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/btts/prodCons.csv
        timeout 120 /usr/bin/time -ao ../../src/CSV/btts/prodCons.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../../src/CSV/btts/philosophes.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/btts/philosophes.csv
        timeout 120 /usr/bin/time -ao ../../src/CSV/btts/philosophes.csv -f %e ./philo.out $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../../src/CSV/btts/readerWriter.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/btts/readerWriter.csv
        timeout 120 /usr/bin/time -ao ../../src/CSV/btts/readerWriter.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"