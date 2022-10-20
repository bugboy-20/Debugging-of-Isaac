CC = g++
CFLAGS = -lncurses -lm -I./include/ -g
SOURCES = ./src/*.cpp

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
	ADDITIONAL_FLAG = 
	RM = del
else
	detected_OS := $(shell uname)
	ADDITIONAL_FLAG = -fsanitize=address
endif

all: main run clean

main: 
	$(CC) $(SOURCES) $(CFLAGS) $(ADDITIONAL_FLAG) -o main

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
