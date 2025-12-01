#!/usr/bin/env bash

last_day=$(find . -mindepth 1 -maxdepth 1 -type d | grep "day[0-9][0-9]" | sort | tail -n 1)
last_day=${last_day#*day}
last_day=$((10#$last_day))
next_day=$(( last_day + 1 ))
folder=$(printf "day%02d" $next_day)

mkdir $folder
pushd $folder
touch main.cpp input input_test
popd