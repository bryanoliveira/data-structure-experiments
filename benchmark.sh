#!/bin/bash
TRIALS=10

echo "Building..."
make clean
make LINEAR_PROBING=1
cp hashmap hashmap-l
make clean
make
cp hashmap hashmap-q


function run_exp {
    echo "Running experiment..."
    ./hashmap-l -i "inputs/$1.txt" --tsv > "outputs/run_"$1"_linear.tsv"
    ./hashmap-q -i "inputs/$1.txt" --tsv > "outputs/run_"$1"_quad.tsv"
}

exp="in_max"
for i in $(seq 1 $TRIALS); do
    run=$exp"_"$i
    if [ ! -f "inputs/$run.txt" ]; then
        echo "Generating data..."
        python generate_data.py -f "inputs/$run.txt" -m 7853 -i 10000 -r 0 -c 1 -s $RANDOM -v
    fi
    run_exp $run
done

exp="in_max_noprime"
for i in $(seq 1 $TRIALS); do
    run=$exp"_"$i
    if [ ! -f "inputs/$run.txt" ]; then
        echo "Generating data..."
        python generate_data.py -f "inputs/$run.txt" -m $(shuf -i 1000-9999 -n 1) -i 10000 -r 0 -c 1 -s $RANDOM -v
    fi
    run_exp $run
done
