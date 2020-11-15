SRC_DIR = ./src
SOURCE = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(patsubst %.cc, %.o, $(SOURCE))
TARGET = ../../../IO/main
INCLUDE = -I./inc -I/home/invrise/OpenBLAS/include/

CC = g++
LIBS = -lm -lopenblas -L/home/invrise/OpenBLAS/lib
CFLAGS = -c -Wall -msse4.1 -mfma -mavx2 -fopenmp -ggdb -Ofast
LDFLAGS = -Wall -fopenmp

$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
%.o : %.cc
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE)

.PHONY : clean
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)