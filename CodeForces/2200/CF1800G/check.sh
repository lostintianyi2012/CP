#!/bin/bash

while true; do
    ./generator > input.txt
    ./CF1800G_std < input.txt > ans.txt
    ./CF1800G < input.txt > output.txt
    if diff ans.txt output.txt; then
        printf "Accepted\n"
    else
        printf "Wrong Answer\n"
		break
    fi
	sleep 0.2
done
