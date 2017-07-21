#!/bin/sh

path="outputs/"
gr="greedy_"
th="theta_"
ext=".dot"
se="_ser_"
pa="_par_"
for nb_pts in 50 100 200
do
  echo "$nb_pts points:\n"
  # GREEDY
  echo "Greedy\n"
  for e in 1.1 1.2 1.4 1.8 2 4 8
  do
    # SERIAL
    echo "Serial e = $e"
    ./spanner -sgc $nb_pts -e $e -o "$path$gr$nb_pts$se$e$ext"
    # PARALLEL
    echo "Parallel e = $e"
    ./spanner -pgc $nb_pts -e $e -o "$path$gr$nb_pts$pa$e$ext"
  done
  # THETA
  echo "Theta\n"
  for k in 2 4 8 16 32 64
  do
    # SERIAL
    echo "Serial k = $k"
    ./spanner -stc $nb_pts -k $k -o "$path$th$nb_pts$se$c$ext"
    # PARALLEL
    echo "Parallel k = $k"
    ./spanner -ptc $nb_pts -k $k -o "$path$th$nb_pts$pa$c$ext"
  done
done
