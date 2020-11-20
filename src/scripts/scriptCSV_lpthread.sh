#!/bin/bash
cd ../lpthread
echo "Nbr threads,Time">../CSV/lpthread/prodCons.csv
gcc producer_consumer.c -o outprod -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/lpthread/prodCons.csv
        /usr/bin/time -ao ../CSV/lpthread/prodCons.csv -f %e ./outprod $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../CSV/lpthread/philosophes.csv
gcc philosophes.c -o outphilo -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/lpthread/philosophes.csv
        /usr/bin/time -ao ../CSV/lpthread/philosophes.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../CSV/lpthread/readerWriter.csv
gcc readers_writers.c -o outRW -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/lpthread/readerWriter.csv
        /usr/bin/time -ao ../CSV/lpthread/readerWriter.csv -f %e ./outRW $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"