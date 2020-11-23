#!/bin/bash
cd output/test_and_test_and_set
echo "Nbr threads,Time">../../src/CSV/tts/prodCons.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/tts/prodCons.csv
        /usr/bin/time -ao ../../src/CSV/tts/prodCons.csv -f %e ./prod_cons.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Producter consumer done"


echo "Nbr threads,Time">../../src/CSV/tts/philosophes.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/tts/philosophes.csv
        /usr/bin/time -ao ../../src/CSV/tts/philosophes.csv -f %e ./philo.out $j 
    done
done
echo "Philosophes done"


echo "Nbr threads,Time">../../src/CSV/tts/readerWriter.csv
for j in $(seq 2 $1);do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>../../src/CSV/tts/readerWriter.csv
        /usr/bin/time -ao ../../src/CSV/tts/readerWriter.csv -f %e ./read_write.out $(($j/2)) $((($j+1)/2))
    done
done
echo "Readers writers done"