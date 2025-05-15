#$PREFIX/bin/bash

echo "  TEST  C test..."
gcc main.c -I../genisi -L../ -lgenisi -o main
./main
echo "  TEST  Java test..."
export LD_LIBRARY_PATH=..
javac Genisi.java
java Genisi

rm main
rm Genisi.class