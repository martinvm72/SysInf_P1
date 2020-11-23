#!/bin/bash
cd output/test_and_set
echo "Nbr threads,Time">../../src/CSV/ts/prodConsAWS.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/prodConsAWS.csv
        /usr/bin/time -ao ../../src/CSV/ts/prodConsAWS.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../../src/CSV/ts/philosophesAWS.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/philosophesAWS.csv
        /usr/bin/time -ao ../../src/CSV/ts/philosophesAWS.csv -f %e ./philo.out $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../../src/CSV/ts/readerWriterAWS.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/ts/readerWriterAWS.csv
        /usr/bin/time -ao ../../src/CSV/ts/readerWriterAWS.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"