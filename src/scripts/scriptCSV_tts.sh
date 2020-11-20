#!/bin/bash
cd ../test_and_test_and_set
echo "Nbr threads,Time">../CSV/tts/prodCons.csv
gcc producer_consumer_tts.c -o outprod -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/tts/prodCons.csv
        /usr/bin/time -ao ../CSV/tts/prodCons.csv -f %e ./outprod $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../CSV/tts/philosophes.csv
gcc philosophes_tts.c -o outphilo -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/tts/philosophes.csv
        /usr/bin/time -ao ../CSV/tts/philosophes.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../CSV/tts/readerWriter.csv
gcc readers_writers_tts.c -o outRW -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../CSV/tts/readerWriter.csv
        /usr/bin/time -ao ../CSV/tts/readerWriter.csv -f %e ./outRW $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"