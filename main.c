#include <stdio.h>
#include <ctype.h>
#include "configuration.h"
#include "pavillion.h"

/*===================================
            Prototypes
===================================*/

void commandline(pavillion p);
void docommand_E(char* command);
void docommand_F(int* num_tax);
void docommand_L();
void docommand_T(); // Trampolim vazio.\n
void docommand_S();
void docommand_V();
void docommand_Q();
void docommand_C();
void docommand_P(); // fila de trampolins
void docommand_X();


/*===================================
               Main
===================================*/

int main()
{
    // Variables
    char command[MAX_INPUT];
    int num_trampolines;

    if (!DEBUG_MODE)
    {
        // Fill the variables with input
        fgets(command, MAX_INPUT, stdin);
        sscanf(command,"%d",&num_trampolines);
    }
    else
        num_trampolines = 4;

    // Create our pavillion and go to the command line
    pavillion p = create_pavillion(num_trampolines);
    if (p != NULL)
        commandline(p);

    // If we exit the command line, free the memory
    destroy_pavillion(p);
    return 0;
}


/*===================================
            docommand_E
    Add a person to the pavillion
===================================*/

void docommand_E(char* command)
{
    // Variables
    int num_id = 64, num_tax = 64;
    char name[MAX_INPUT] = "John Doe";

    if (!DEBUG_MODE)
    {
        // Read and ask for information
        sscanf(command, "E %d %d", &num_tax, &num_id);
        fgets(name, MAX_INPUT, stdin);
    }

    // Add the client to the pavillion
    if (pavillion_add_client(num_id, num_tax, name) == 1)
        printf("Entrada autorizada\n");
    else
        printf("Visitante ja no pavilhao\n");
}


/*===================================
            commandline
    Read commands from the user
===================================*/

void commandline(pavillion p)
{
    char command[MAX_INPUT]; // Command to read.
    
    // Read commands until the heat death of the universe.
    while (1) 
    {
        // Get a string from user input
        fgets(command, MAX_INPUT, stdin); 
        
        switch(toupper(command[0]))
        {
            case 'E': docommand_E(command); break;
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