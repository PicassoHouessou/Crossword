#! /bin/bash

tab=(`find tmp/sauvegardes/  -type f -name *.txt`)

for (( i=0;i<${#tab[@]};i++ ));do
    rm -r ${tab[i]}
done