CC = gcc
CFLAGS = -I./lib -I./genisi -fPIC
STATIC = -llog -ldl
OBJS = src/android/android.o src/android/android_sys.o src/android/android_memory.o src/android/android_linker.o src/android/android_debug.o src/javaApi/binding.o src/javaApi/functions.o src/javaApi/prefabs.o

all:
	@echo "Compiling objects android..."
	@echo "Compiling object src/android/android.o..."
	@$(CC) $(CFLAGS) -c src/android/android.c -o src/android/android.o
	@echo "Compiling object src/android/android_sys.o..."
	@$(CC) $(CFLAGS) -c src/android/android_sys.c -o src/android/android_sys.o
	@echo "Compiling object src/android/android_memory.o..."
	@$(CC) $(CFLAGS) -c src/android/android_memory.c -o src/android/android_memory.o
	@echo "Compiling object src/android/android_linker.o..."
	@$(CC) $(CFLAGS) -c src/android/android_linker.c -o src/android/android_linker.o
	@echo "Compiling object src/android/android_debug.o.."
	@$(CC) $(CFLAGS) -c src/android/android_debug.c -o src/android/android_debug.o
	@echo "Compiling objects javaApi..."
	@echo "Compiling object src/javaApi/binding.c..."
	@$(CC) $(CFLAGS) -c src/javaApi/binding.c -o src/javaApi/binding.o
	@echo "Compiling object src/javaApi/functions.o..."
	@$(CC) $(CFLAGS) -c src/javaApi/functions.c -o src/javaApi/functions.o
	@echo "Compiling object src/javaApi/prefabs.o..."
	@$(CC) $(CFLAGS) -c src/javaApi/prefabs.c -o src/javaApi/prefabs.o
	@echo "Compiling shared library version linker src/genisi.version..."
	@$(CC) $(STATIC) -L./lib -fPIC -Wl,-rpath-link,/system/lib -shared $(OBJS) -o libgenisi.so
	@$(MAKE) Oclear
Oclear:
	@find . -type f -name "*.o" -exec rm -f {} \;
clear:
	@echo "clear..."
	@rm libgenisi.so*
exemple:
	@$(CC) -g -L./ -I./genisi test/main.c -o exemple -lgenisi
