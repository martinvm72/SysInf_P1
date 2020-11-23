#!/bin/bash
cd output/lpthread
echo "Nbr threads,Time">../../src/CSV/lpthread/prodCons.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/lpthread/prodCons.csv
        /usr/bin/time -ao ../../src/CSV/lpthread/prodCons.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../../src/CSV/lpthread/philosophes.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/lpthread/philosophes.csv
        /usr/bin/time -ao ../../src/CSV/lpthread/philosophes.csv -f %e ./philo.out $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../../src/CSV/lpthread/readerWriter.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/lpthread/readerWriter.csv
        /usr/bin/time -ao ../../src/CSV/lpthread/readerWriter.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"