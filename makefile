SRC_DIR := ./source
INC_DIR := ./include
OBJ_DIR := ./object
SQL_DIR := ./sqlite
CXX := g++
CC := gcc
CFLAGS := -std=c++17 -g
LDFLAGS := -lpthread -ldl
TARGET := assignment5
INC := -I include/

SRCS := $(wildcard $(SRC_DIR)/*.cpp assignment5.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(SQL_DIR)/sqlite.o $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^
$(SQL_DIR)/sqlite.o: $(SQL_DIR)/*.c
	$(CC) -o $@ -shared $^ $(LDFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $< $(INC)
clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o
	
.PHONY: all clean