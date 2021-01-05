SRC_DIR = ./src
OBJ_DIR = ./bin
SOURCE = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(notdir $(SOURCE)))
TARGET = ./build/main
INCLUDE = -I./inc

CC = g++
LIBS = -lm
CFLAGS = -c -Wall -fopenmp -ggdb -Ofast -std=c++2a
CVFLAGS = `pkg-config --cflags opencv4`
CVLIBS = `pkg-config --libs opencv4`
LDFLAGS = -Wall -fopenmp

$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) $(CVLIBS) -o $@
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(CC) $(CFLAGS) $(CVFLAGS) $< -o $@ $(INCLUDE)

.PHONY : clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)