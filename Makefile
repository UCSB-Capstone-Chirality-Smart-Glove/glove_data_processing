CFLAGS = -g -O0 -Wall

glove:
		gcc main.c finger.c hand.c util.c -o glove ${CFLAGS}

test: 
		gcc main.c finger.c hand.c util.c testing/util_test.c -o test ${CFLAGS}
		./test

clean:
		rm -f glove *.exe *.o