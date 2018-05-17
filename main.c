#include <stdio.h>
#include <ctype.h>

/*===================================
            Definitions
===================================*/

#define MAX_INPUT       140
#define MAX_TRAMPOLINES 500
#define MAX_STOCK       3000


/*===================================
            Prototypes
===================================*/

void commandline();
void docommand_E();
void docommand_F();
void docommand_L();
void docommand_T();
void docommand_S();
void docommand_V();
void docommand_Q();
void docommand_C();
void docommand_P();
void docommand_X();


/*===================================
               Main
===================================*/

int main()
{
    commandline();
    return 0;
}


/*===================================
            commandline
===================================*/

void commandline()
{
    char s[MAX_INPUT] = "\0"; // Command to read.
    
    // Read commands until the heat death of the universe.
    while (1) 
    {
        // Get a string from user input
        fgets(s, 140, stdin); 
        
        switch(toupper(s[0]))
        {
            case 'E': break;
            case 'F': break;
            case 'L': break;
            case 'T': break;
            case 'S': break;
            case 'V': break;
            case 'Q': break;
            case 'C': break;
            case 'P': break;
            case 'X': return;
            default:  printf("Comando invalido.\n"); break; // Error
        }
    }

}