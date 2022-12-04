#!/bin/bash

./bin/PathFinder > t.txt
./bin/seperate < t.txt
rm t*.txt
