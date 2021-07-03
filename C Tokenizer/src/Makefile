GUI.o: GUI.c tokenizer.h history.h
	gcc -o GUI.c tokenizer.o hostory.o
tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c
main: tokenizer.o GUI.o history.o
	gcc -c test tokenizer.o GUI.o history.o
history: history.c histoory.h
	gcc -c history.c

clean: rm -f test *.o *~ *#
