#!/bin/bash

run_with_time() {
    local program=$1
    local label=$2
    local filename=$3
    local int_arg=$4
    local float_arg=$5
    
    if [ ! -f "$program" ]; then
        echo "Error: Executable '$program' not found!"
        return 1
    fi
    
    if [ ! -f "$filename" ]; then
        echo "Error: Input file '$filename' not found!"
        return 1
    fi
    
    echo "===== Running $label ====="
    echo "Arguments:"
    echo "  Filename: $filename"
    echo "  Integer: $int_arg"
    echo "  Float: $float_arg"
    echo ""
    
    /usr/bin/time -f "\nCommand: %C\nExit status: %x\n\nReal time: %e s\nUser time: %U s\nSystem time: %S s\nCPU usage: %P\nMax memory: %M KB" \
        ./"$program" "$filename" "$int_arg" "$float_arg" 2>&1
    
    echo -e "\n"
}

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <filename> <integer> <float>"
    echo "Example: $0 example.bmp 5 3.14"
    exit 1
fi


if ! [[ "$2" =~ ^[0-9]+$ ]]; then
    echo "Error: Second argument must be an integer"
    exit 1
fi

run_with_time "output" "Sequential Version" "$1" "$2" "$3"
run_with_time "outputParallel" "Parallel Version" "$1" "$2" "$3"

echo "All executions completed"
