#!/bin/bash

export AITUNING_FIRST_RUN=1

mpirun -np $2 ./$1

export AITUNING_FIRST_RUN=0

mv performance_variables.txt old_performance_variables.txt

mpirun -np $2 ./$1

python3 MPICH_DQN_parabola_Q_learning.py

for i in `seq 1 $3`;
do
    mv performance_variables.txt old_performance_variables.txt
    mpirun -np $2 ./$1
    python3 MPICH_DQN_parabola_Q_learning.py
    cat changes.txt
done    
