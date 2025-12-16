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

mkdir -p day$day

cp template/* day$day/
curl -s -o day$day/input.txt https://adventofcode.com/$year/day/$((10#$day))/input -H "cookie: session=$cookie"
sed -i "s/{day_number}/$day/g" ~/AdventOfCode/2024/day$day/Makefile

echo "Done."
