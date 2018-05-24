PROGRAM			= pavilion
CODEFILES 		= main.c client.c

CODEOBJECTS		= $(CODEFILES:.c=.o)

default:
	@gcc -c $(CODEFILES) -Wall
	@gcc -o $(PROGRAM) $(CODEOBJECTS) 
	@rm *.o