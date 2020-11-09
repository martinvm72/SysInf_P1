#!/bin/bash
echo "Nbr threads, Time">prodCons.csv
gcc producer_consumer.c -o outprod -lpthread
for j in {3..15..2};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>prodCons.csv
        /usr/bin/time -ao prodCons.csv -f %e ./outprod $(($j/2)) $(($j/2+1))
    done
done
for j in {2..16..2};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>prodCons.csv
        /usr/bin/time -ao prodCons.csv -f %e ./outprod $(($j/2)) $(($j/2))
    done
done
echo "prod done"