#!/bin/bash
fltk-config --compile computers.cpp
i=1
touch stats*
rm stats*
while [ $i -lt 7 ]
do
echo "depth: "$i >>stats
./computers 1 2 $i 0 > game12
./computers 1 3 $i 0 > game13
./computers 1 4 $i 0 > game14
./computers 2 1 $i 0 > game21
./computers 2 3 $i 0 > game23
./computers 2 4 $i 0 > game24
./computers 3 1 $i 0 > game31
./computers 3 2 $i 0 > game32
./computers 3 4 $i 0 > game34
./computers 4 1 $i 0 > game41
./computers 4 2 $i 0 > game42
./computers 4 3 $i 0 > game43
echo "coins parity heuristic as player 1:" >> stats
tail -1 game12 >> stats
tail -1 game13 >> stats
tail -1 game14 >> stats
echo "stability heuristic as player 1:" >> stats
tail -1 game21 >> stats
tail -1 game23 >> stats
tail -1 game24 >> stats
echo "corner heuristic as player 1:" >> stats
tail -1 game31 >> stats
tail -1 game32 >> stats
tail -1 game34 >> stats
echo "mobility heuristic as player 1:" >> stats
tail -1 game41 >> stats
tail -1 game42 >> stats
tail -1 game43 >> stats
i=$[$i+1]
done
rm game*
