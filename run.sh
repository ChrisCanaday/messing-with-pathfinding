./bin/PathFinder > t.txt
./jgraph/jgraph -P t.txt | ps2pdf - | convert -density 300 - -quality 100 t.png