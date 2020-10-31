SRC_DIR = ./src
SOURCE = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(patsubst %.cc, %.o, $(SOURCE))
TARGET = ../../../IO/main
INCLUDE = -I./inc

CC = g++
LIBS = -lm
CFLAGS = -c -Wall

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)
%.o : %.cc
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE)

.PHONY : clean
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)