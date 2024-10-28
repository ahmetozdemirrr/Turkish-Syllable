CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -Iinclude
LDFLAGS = -shared
TARGET = libsyllable.so
SRC_DIR = src
INCLUDE_DIR = include

all: $(TARGET)

$(TARGET): $(SRC_DIR)/syllable.o
	$(CC) $(LDFLAGS) -o $@ $^

$(SRC_DIR)/syllable.o: $(SRC_DIR)/syllable.c $(INCLUDE_DIR)/syllable.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

test: all
	$(CC) $(SRC_DIR)/syllable_processor.c -o syllable_processor -I$(INCLUDE_DIR) -L. -lsyllable -Wall -Wextra
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH && ./syllable_processor
