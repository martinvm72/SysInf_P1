#!/bin/bash
cd ../test_and_set
echo "Nbr threads,Time">../CSV/ts/prodConsAWS.csv
gcc producer_consumer_ts.c -o outprod -lpthread
for j in {2..4};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/ts/prodConsAWS.csv
        /usr/bin/time -ao ../CSV/ts/prodConsAWS.csv -f %e ./outprod $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../CSV/ts/philosophesAWS.csv
gcc philosophes_ts.c -o outphilo -lpthread
for j in {2..4};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/ts/philosophesAWS.csv
        /usr/bin/time -ao ../CSV/ts/philosophesAWS.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../CSV/ts/readerWriterAWS.csv
gcc readers_writers_ts.c -o outRW -lpthread
for j in {2..4};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/ts/readerWriterAWS.csv
        /usr/bin/time -ao ../CSV/ts/readerWriterAWS.csv -f %e ./outRW $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"
