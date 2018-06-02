#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // For debugging
#include <time.h>   // For debugging
#include "configuration.h"
#include "client.h"
#include "food.h"
#include "pavilion.h"


/*===================================
              Prototypes
===================================*/

void commandline(pavilion p);
void docommand_E(pavilion p, char* command);
void docommand_F(pavilion p, char* command);
void docommand_L(pavilion p, char* command);
void docommand_T(pavilion p, char* command); // Trampolim vazio.\n
void docommand_S(pavilion p, char* command);
void docommand_V(pavilion p, char* command);
void docommand_Q(pavilion p, char* command);
void docommand_C(pavilion p);
void docommand_P(pavilion p); // fila de trampolins
void docommand_X(pavilion p); 


/*===================================
                 Main               
===================================*/

int main()
{
    // Generate a random seed (for debugging)
    srand(time(NULL));

    // Create our pavilion and make sure it works
    pavilion p = pavilion_create();
    if (p == NULL)
        return 0;
        
    // Go to the command line
    commandline(p);

    // If we exit the command line, close the pavilion and free the memory
    pavilion_destroy(p);
    return 0;
}


/*===================================
             commandline            
     Read commands from the user
===================================*/

void commandline(pavilion p)
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
            case 'V': docommand_V(p, command); break;
            case 'Q': docommand_Q(p, command); break;
            case 'C': docommand_C(p); break;
            case 'P': docommand_P(p); break; // ALOMST DONE (NEED TO PRINT TRAMPOLINE NUMBER)
            case 'X': docommand_X(p); return;
            case '\n': break;
            default:  printf("Dados invalidos.\n"); break; // Error
        }
    }

}


/*===================================
             docommand_E            
    Add a person to the pavilion
===================================*/

void docommand_E(pavilion p, char* command)
{
    // Variables
    int num_id, num_tax;
    char name[MAX_INPUT];

    // Ask for information (or generate some if debugging)
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

    // Add the client to the pavilion
    if (pavilion_add_client(p, name, num_id, num_tax) == SUCCESS)
        printf("Entrada autorizada.\n");
    else
        printf("Visitante ja no pavilhao.\n");
}


/*===================================
             docommand_F
 Add a person to the trampoline line
===================================*/

void docommand_F(pavilion p, char* command)
{
    // Variables
    int num_id;
    client c;

    // Read the command and check if the client is valid
    sscanf(command, "F %d", &num_id);
    if (pavilion_exists_client(p, num_id) == FALSE)
    {
        printf("Visitante nao esta no pavilhao.\n");
        return;
    }
    c = pavilion_get_client(p, num_id);

    // Interpret the command
    if (client_get_location(c) != LOCATION_BAR)
        printf("Chegada nao autorizada a fila.\n");
    else
    {
        client_set_location(c, LOCATION_LINE);
        printf("Chegada autorizada a fila.\n");
    }
}


/*===================================
             docommand_V
    Purchase an item from the bar
===================================*/

void docommand_V(pavilion p, char* command)
{
    // Variables
    int num_id, amount;
    char item;
    client c;

    // Read the command
    sscanf(command, "V %c %d %d", &item, &amount, &num_id);
    item = toupper(item);

    // Make sure the client is valid
    if (pavilion_exists_client(p, num_id) == FALSE)
    {
        printf("Visitante nao esta no pavilhao.\n");
        return;
    }
    c = pavilion_get_client(p, num_id);

    // Make sure that we can purchase the food, and if so make the purchase
    if (client_get_location(c) != LOCATION_BAR)
        printf("Venda nao autorizada.\n");
    else if (pavilion_exists_food(p, item) == FALSE || food_get_stock(pavilion_get_food(p, item)) < amount)
        printf("Produto %c esgotado.\n", item);
    else
    {
        food f = pavilion_get_food(p, item);
        client_set_bill(c, client_get_bill(c) + food_get_price(f)*amount);
        food_set_stock(f, food_get_stock(f) - amount);
        printf("Venda autorizada.\n");
    }
}


/*===================================
             docommand_Q
  Remove a person from the pavilion
===================================*/

void docommand_Q(pavilion p, char* command)
{
    // Variables
    int num_id;
    float bill;
    client c;

    // Read the command and check if the client is valid
    sscanf(command, "Q %d", &num_id);
    if (pavilion_exists_client(p, num_id) == FALSE)
    {
        printf("Visitante nao esta no pavilhao.\n");
        return;
    }
    c = pavilion_get_client(p, num_id);

    if (client_get_location(c) != LOCATION_BAR)
        printf("Saida nao autorizada.\n");
    else
    {
        bill = client_get_bill(c) + (1+((max((float)client_get_time(c)-1,0))/30))*5;
        pavilion_set_cash(p, pavilion_get_cash(p) + bill);
        pavilion_remove_client(p, num_id);
        printf("Saida autorizada, valor a pagar %.2f euros.\n", bill);
    }
}


/*===================================
             docommand_C
           Print the cash
===================================*/

void docommand_C(pavilion p)
{
    printf("Caixa: %.2f euros.\n", pavilion_get_cash(p));
}


/*===================================
             docommand_P
Print a list of people alphabetically
===================================*/

void docommand_P(pavilion p)
{
    int size;
    size = pavilion_count_clients(p);
    if (size == 0)
        printf("Sem visitantes no pavilhao.\n");
    else
    {
        pavilion_display_clients(p);
    }
}


/*===================================
             docommand_X
 Print the final information before
         exiting the program
===================================*/

void docommand_X(pavilion p)
{
    int i;
    pavilion_close(p);
    printf("Caixa: %.2f euros.\n", pavilion_get_cash(p));
    for (i=0;i<NUM_FOOD;i++)
    {
        char key = food_get_key_from_index(i);
        food f = pavilion_get_food(p, key);
        if (f == NULL)
            return;
        printf("Stock %s: %d\n", food_get_name(f), food_get_stock(f));
    }
}