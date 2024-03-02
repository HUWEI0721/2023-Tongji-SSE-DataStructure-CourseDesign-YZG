CC = g++
CFLAGS = -c
LFLAGS = 
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
SRC = $(patsubst %.cpp, %, $(wildcard *.cpp))
all: $(OBJS)
	$(CC) $(LFLAGS) $^ -o AI_01_2153393_HuJunwei
$(OBJS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
