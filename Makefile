SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play
INCLUDE = -Iinclude
C_FLAGS = -W
LINKER_FLAGS = -lSDL2 -lSDL2_image

all:
	$(CC) $(INCLUDE) $(SRC_FILES) $(C_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)
