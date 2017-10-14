OBJ = test.o max.o min.o

test:$(OBJ)
	gcc -o test $(OBJ)
test.o:test.c
	@echo "开始编译test.c"
	gcc -o test.o -c test.c
	@echo "编译结束test.c"
max.o:max.c
	@echo "开始编译max.c"
	gcc -o max.o -c max.c
	@echo "编译结束max.c"
min.o:min.c
	gcc -o min.o -c min.c
clean:
	@echo "开始删除"
	rm $(OBJ) test
	@echo "删除结束"
