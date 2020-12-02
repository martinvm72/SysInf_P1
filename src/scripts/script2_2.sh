#!/bin/bash
cd output/T22
echo "Tests des verrous test_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/Tache2_2/ts.csv
for i in $(seq 1 $1);do
    for j in {1..5};do
        echo -n "$i,">>../../src/CSV/Tache2_2/ts.csv
        /usr/bin/time -ao ../../src/CSV/Tache2_2/ts.csv -f %e ./ts.out $(($i))
    done
    echo "Fini pour $i thread(s)"
done
echo "Tests des verrous test_and_set en terminés"

echo "Tests des verrous test_and_test_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/Tache2_2/tts.csv
for i in $(seq 1 $1);do
    for j in {1..5};do
        echo -n "$i,">>../../src/CSV/Tache2_2/tts.csv
        /usr/bin/time -ao ../../src/CSV/Tache2_2/tts.csv -f %e ./tts.out $(($i))
    done
    echo "Fini pour $i thread(s)"
done
echo "Tests des verrous test_and_test_and_set en terminés"

echo "Tests des verrous backoff_test_and_test_and_set en cours..."
echo "Nbr threads,Time">../../src/CSV/Tache2_2/btts.csv
for i in $(seq 1 $1);do
    for j in {1..5};do
        echo -n "$i,">>../../src/CSV/Tache2_2/btts.csv
        /usr/bin/time -ao ../../src/CSV/Tache2_2/btts.csv -f %e ./btts.out $(($i))
    done
    echo "Fini pour $i thread(s)"
done
echo "Tests des verrous backoff_test_and_test_and_set en terminés"