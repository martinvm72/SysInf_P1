#!/bin/bash
cd output/test_and_set
echo "Nbr threads,Time">../../src/CSV/ts/prodCons.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/prodCons.csv
        timeout 120 /usr/bin/time -ao ../../src/CSV/ts/prodCons.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../../src/CSV/ts/philosophes.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/philosophes.csv
        timeout 120 /usr/bin/time -ao ../../src/CSV/ts/philosophes.csv -f %e ./philo.out $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../../src/CSV/ts/readerWriter.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/readerWriter.csv
        timeout 120 /usr/bin/time -ao ../../src/CSV/ts/readerWriter.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"