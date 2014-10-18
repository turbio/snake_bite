CC = g++
CFLAGS = -Wall -g
LIBS = -lalleg
TARGET = snake_bite

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) $^
