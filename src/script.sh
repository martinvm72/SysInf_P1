#!/bin/bash
echo "Nbr threads, Time">philosophes2.csv
gcc philosophes.c -o outphilo -lpthread
for j in {2..16};do
    echo $j
    for i in {1..5};do
        echo -n "$j,">>philosophes2.csv
        /usr/bin/time -ao philosophes2.csv -f %e ./outphilo $j 
    done
done
echo "Philosophes done"