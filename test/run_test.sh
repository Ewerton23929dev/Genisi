#$PREFIX/bin/bash
export LD_LIBRARY_PATH=.
echo "  TEST  C test..."
gcc test/main.c -Igenisi -L. -lgenisi -o main
./main
echo "  TEST  Java test..."
javac test/Genisi.java
java -cp test Genisi

rm main
rm test/Genisi.class