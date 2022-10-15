CC = g++
CFLAGS = -lncurses -lm -I./include/ -g -fsanitize=address
SOURCES = ./src/*.cpp

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname)
endif

all: main run clean

main: 
	$(CC) $(SOURCES) $(CFLAGS) -o main

run:
ifeq ($(detected_OS), Windows)
	.\main.exe
else
	./main 2> errors
endif

clean:
ifeq ($(detected_OS), Windows)
	del main.exe
else
	rm main
endif
