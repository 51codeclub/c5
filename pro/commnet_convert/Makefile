cct:convert.o convertcomment.o log.o
	gcc -o cct convert.o convertcomment.o log.o
convert.o:convert.c
	gcc -o convert.o -c convert.c -g
convertcomment.o:convertcomment.c
	gcc -o convertcomment.o -c convertcomment.c -g
log.o:log.c
	gcc -o log.o -c log.c -g
clean:
	rm *.o cct
