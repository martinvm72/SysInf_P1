#!/bin/bash
echo "Nbr threads,Time">CSV/prodCons.csv
gcc producer_consumer.c -o outprod -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>CSV/prodCons.csv
        /usr/bin/time -ao CSV/prodCons.csv -f %e ./outprod $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">CSV/philosophes.csv
gcc philosophes.c -o outphilo -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>CSV/philosophes.csv
        /usr/bin/time -ao CSV/philosophes.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">CSV/readerWriter.csv
gcc readers_writers.c -o outRW -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>CSV/readerWriter.csv
        /usr/bin/time -ao CSV/readerWriter.csv -f %e ./outRW $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"