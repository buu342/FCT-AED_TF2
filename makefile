PROGRAM			= pavilion
CODEFILES 		= main.c client.c food.c slot.c trampoline.c pavilion.c

ALGORITHMS		= quicksort.c

ADTS			= $(ADT_ITERATOR) $(ADT_DICTIONARY) $(ADT_SEQUENCE) $(ADT_QUEUE)
ADT_ITERATOR	= iteraVector.c
ADT_DICTIONARY	= dicVector.c chaves.c tuplo.c
ADT_QUEUE		= filaVec.c
ADT_SEQUENCE 	= seqVector.c

CODEOBJECTS		= $(CODEFILES:.c=.o) $(ALGORITHMS:.c=.o) $(ADTS:.c=.o)

default:
	@gcc -c $(CODEFILES) $(ALGORITHMS) $(ADTS) -Wall
	@gcc -o $(PROGRAM) $(CODEOBJECTS) 
	@rm *.o