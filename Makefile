GCC = gcc 
CFLAGS = -g -Wall -Wshadow

duckbits:  duck.o  
	$(GCC) $(CFLAGS) duck.o -o duckbits

duck.o: duck.c
	$(GCC) $(CFLAGS)  -c duck.c

bitwise_op.o: bitwise_op.c
	$(GCC) $(CFLAGS)  -c bitwise_op.c

sample:
	make duckbits
	./duckbits