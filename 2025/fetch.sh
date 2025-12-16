#!/bin/bash
year=2025

if [ -z "$1" ]; then
    # Ask for the day
    read -p "Enter the day: " day
else
    day=$1
fi

day=$(printf "%02d" $day)
cookie=$(cat .env)

mkdir -p ~/AdventOfCode/$year/day$day

cp ~/AdventOfCode/$year/template/* ~/AdventOfCode/$year/day$day/
curl -s -o ~/AdventOfCode/$year/day$day/input.txt https://adventofcode.com/$year/day/$((10#$day))/input -H "cookie: session=$cookie"

echo "Done."
