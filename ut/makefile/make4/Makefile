OBJ = test.o max.o min.o
CC = gcc
CFLAGS = -g -Wall

test:$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
test.o:test.c
	$(CC) $(CFLAGS) -o $@ -c $^
max.o:max.c
	$(CC) $(CFLAGS) -o $@ -c $^
min.o:min.c
	$(CC) $(CFLAGS) -o $@ -c $^
clean:
	rm *.o test
