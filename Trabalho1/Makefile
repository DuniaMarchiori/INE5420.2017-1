INCLUDE=include/

SOURCE_FILES=$(wildcard ./*.cpp)
# SOURCE_FILES=$(wildcard ./*.hpp) $(wildcard ./*.cpp)
all: $(SOURCE_FILES)
	g++ `pkg-config --cflags gtk+-3.0` -o Trabalho1 -Iinclude/ -I../Include/ $(SOURCE_FILES) `pkg-config --libs gtk+-3.0` -std=c++11 -rdynamic
clean:
	rm Trabalho1
