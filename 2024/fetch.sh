#!/bin/bash

if [ -z "$1" ]; then
    # Ask for the day
    read -p "Enter the day: " day
else
    day=$1
fi

day=$(printf "%02d" $day)


mkdir -p ~/AdventOfCode/2024/day$day

cp ~/AdventOfCode/2024/template/* ~/AdventOfCode/2024/day$day/
# in main.cpp replace {day_number} with $day
sed -i "s/{day_number}/$day/g" ~/AdventOfCode/2024/day$day/main.cpp
curl -s -o ~/AdventOfCode/2024/day$day/input.txt https://adventofcode.com/2024/day/$((10#$day))/input

echo "Done."
