CFLAGS = -Wall -fpic -coverage -lm

testme:
	gcc -o testme -g testme.c $(CFLAGS)
	gcov testme.c >> testmeresults.out
	./testme
clean:
	rm -f testme *.gcov *.gcda *.gcno *.o testmeresults.out