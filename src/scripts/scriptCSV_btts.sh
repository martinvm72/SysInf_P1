#!/bin/bash
cd ../backoff_test_and_test_and_set
echo "Nbr threads,Time">../CSV/btts/prodCons.csv
gcc producer_consumer_btts.c -o outprod -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/btts/prodCons.csv
        /usr/bin/time -ao ../CSV/btts/prodCons.csv -f %e ./outprod $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../CSV/btts/philosophes.csv
gcc philosophes_btts.c -o outphilo -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/btts/philosophes.csv
        /usr/bin/time -ao ../CSV/btts/philosophes.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../CSV/btts/readerWriter.csv
gcc readers_writers_btts.c -o outRW -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/btts/readerWriter.csv
        /usr/bin/time -ao ../CSV/btts/readerWriter.csv -f %e ./outRW $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"