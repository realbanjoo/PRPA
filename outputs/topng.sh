#!/bin/sh
if [ $# -eq 0 ]; then
  for dot in *.dot; do
    echo processing $dot
    name=$(basename -s .dot $dot)
    dot -Kfdp -n -Tpng -o $name.png $dot
  done
else
  for dot in $@; do
    echo processing $dot
    name=$(basename -s .dot $dot)
    dot -Kfdp -n -Tpng -o $name.png $dot
  done
fi
