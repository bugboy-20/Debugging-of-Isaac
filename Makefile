CC = g++
CFLAGS = -lncurses -lm -I./include/ -g
SOURCES = ./src/*.cpp
 

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
	ADDITIONAL_FLAG = 
	RM = del
	EXECUTABLE = main
else
	detected_OS := $(shell uname)
	ADDITIONAL_FLAG = #-fsanitize=address
	EXECUTABLE = main.out
endif

all: main run clean

main: 
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

run:
ifeq ($(detected_OS), Windows)
	.\main.exe
else
	./main.out 2> errors.log
endif

clean:
ifeq ($(detected_OS), Windows)
	del main.exe
else
	rm main.out
endif
