CC = gcc
CFLAGS = -I./lib -I./genisi -L./lib
STATIC = -llog
OBJS = src/android/android.o src/android/android_sys.o

all:
	@echo "Compiling object src/android/android.o..."
	@$(CC) $(CFLAGS) -c src/android/android.c -o src/android/android.o
	@echo "Compiling object src/android/android_sys.o..."
	@$(CC) $(CFLAGS) -c src/android/android_sys.c -o src/android/android_sys.o
	@echo "Compiling shared library version linker src/genisi.version..."
	@$(CC) $(STATIC) -Wl,-rpath-link,/system/lib -shared $(OBJS) -o libgenisi.so
	@$(MAKE) Oclear
Oclear:
	@find . -type f -name "*.o" -exec rm -f {} \;
clear:
	@echo "clear..."
	@rm libgenisi.so*
exemple:
	@$(CC) -L./ -I./genisi test/main.c -o exemple -lgenisi