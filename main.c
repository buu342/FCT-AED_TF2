#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // For debugging
#include <time.h>   // For debugging
#include "configuration.h"
#include "client.h"
#include "pavillion.h"


/*===================================
            Prototypes
===================================*/

void commandline(pavillion p);
void docommand_E(pavillion p, char* command);
void docommand_F(pavillion p, char* command);
void docommand_L(pavillion p, char* command);
void docommand_T(pavillion p, char* command); // Trampolim vazio.\n
void docommand_S(pavillion p, char* command);
void docommand_V(pavillion p, char* command);
void docommand_Q(pavillion p, char* command);
void docommand_C(pavillion p);
void docommand_P(pavillion p); // fila de trampolins


/*===================================
               Main
===================================*/

int main()
{
    // Generate a random seed for debugging
    srand(time(NULL));

    // Create our pavillion and make sure it works
    pavillion p = pavillion_create();
    if (p == NULL)
        return 0;
        
    // Go to the command line
    commandline(p);

    // If we exit the command line, free the memory
    pavillion_destroy(p);
    return 0;
}


/*===================================
            docommand_E
    Add a person to the pavillion
===================================*/

void docommand_E(pavillion p, char* command)
{
    // Variables
    int num_id, num_tax;
    char name[MAX_INPUT];

    // Read and ask for information (or generate some if debugging)
    if (!DEBUG_MODE)
    {
        sscanf(command, "E %d %d", &num_tax, &num_id);
        fgets(name, MAX_INPUT, stdin);
    }
    else
    {
        num_id = rand()%MAX_CLIENTS;
        num_tax = (int)rand();
        sprintf(name, "John Doe %d", num_id);
        printf("%d %d\n%s\n", num_id, num_tax, name);
    }

    // Add the client to the pavillion
    if (pavillion_add_client(p, name, num_id, num_tax) == SUCCESS)
        printf("Entrada autorizada.\n");
    else
        printf("Visitante ja no pavilhao.\n");
}


/*===================================
            docommand_F
  Add a person to the trampline line
===================================*/

void docommand_F(pavillion p, char* command)
{
    // Variables
    int num_id;

    // Read and interpret the command
    sscanf(command, "F %d", &num_id);
    if (pavillion_exists_client(p, num_id) == 0)
        printf("Visitante nao esta no pavilhao.\n");
    else if (client_get_location(pavillion_get_client(p, num_id)) != LOCATION_BAR)
        printf("Chegada nao autorizada a fila.\n");
    else
    {
        client_set_location(pavillion_get_client(p, num_id), LOCATION_LINE);
        printf("Chegada autorizada a fila.\n");
    }
}


/*===================================
            docommand_C
           Print the cash
===================================*/

void docommand_C(pavillion p)
{
    printf("Caixa: %.2f euros.\n", pavillion_get_cash(p));
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
        command[0] = toupper(command[0]);
        switch(command[0])
        {
            case 'E': docommand_E(p, command); break;
            case 'F': docommand_F(p, command); break;
            case 'L': break;
            case 'T': break;
            case 'S': break;
            case 'V': break;
            case 'Q': break;
            case 'C': docommand_C(p); break;
            case 'P': break;
            case 'X': return;
            default:  printf("Dados invalidos.\n"); break; // Error
        }
    }

}