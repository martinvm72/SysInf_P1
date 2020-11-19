#!/bin/bash
cd ../test_and_test_and_set
echo "Nbr threads,Time">prodCons.csv
gcc producer_consumer_tts.c -o outprod -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>prodCons.csv
        /usr/bin/time -ao prodCons.csv -f %e ./outprod $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">philosophes.csv
gcc philosophes_tts.c -o outphilo -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>philosophes.csv
        /usr/bin/time -ao philosophes.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">readerWriter.csv
gcc readers_writers_tts.c -o outRW -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>readerWriter.csv
        /usr/bin/time -ao readerWriter.csv -f %e ./outRW $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"