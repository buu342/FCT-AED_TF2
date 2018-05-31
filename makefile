PROGRAM			= pavillion
CODEFILES 		= main.c pavillion.c client.c 

ADTS			= $(ADT_ITERATOR) $(ADT_DICTIONARY) $(ADT_SEQUENCE) $(ADT_QUEUE)
ADT_ITERATOR	= iteraVector.c
ADT_DICTIONARY	= dicVector.c chaves.c tuplo.c
#ADT_SEQUENCE 	= seqVector.c
#ADT_QUEUE		= filaVec.c

CODEOBJECTS		= $(CODEFILES:.c=.o) $(ADTS:.c=.o)

default:
	@gcc -c $(CODEFILES) $(ADTS) -Wall
	@gcc -o $(PROGRAM) $(CODEOBJECTS) 
	@rm *.o