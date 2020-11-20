#!/bin/bash
cd ../test_and_set
echo "Nbr threads,Time">../CSV/ts/prodCons.csv
gcc producer_consumer_ts.c -o outprod -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/ts/prodCons.csv
        /usr/bin/time -ao ../CSV/ts/prodCons.csv -f %e ./outprod $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../CSV/ts/philosophes.csv
gcc philosophes_ts.c -o outphilo -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/ts/philosophes.csv
        /usr/bin/time -ao ../CSV/ts/philosophes.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../CSV/ts/readerWriter.csv
gcc readers_writers_ts.c -o outRW -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/ts/readerWriter.csv
        /usr/bin/time -ao ../CSV/ts/readerWriter.csv -f %e ./outRW $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"