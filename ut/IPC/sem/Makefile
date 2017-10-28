CFLAGS = -g
SRC = $(wildcard *.c)
TARGET = $(patsubst %.c, %, $(SRC))

#.PHONY:all clean

all: $(TARGET)

%:%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	$(RM) $(TARGET)
