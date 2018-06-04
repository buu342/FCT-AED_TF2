#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "configuration.h"
#include "client.h"
#include "food.h"
#include "pavilion.h"

#if DEBUG_MODE
    #include <time.h>
#endif


/*===================================
              Prototypes
===================================*/

void commandline(pavilion p);
void docommand_E(pavilion p, char* command);
void docommand_F(pavilion p, char* command);
void docommand_L(pavilion p, char* command);
void docommand_T(pavilion p, char* command);
void docommand_S(pavilion p, char* command);
void docommand_V(pavilion p, char* command);
void docommand_Q(pavilion p, char* command);
void docommand_C(pavilion p);
void docommand_P(pavilion p);
void docommand_X(pavilion p); // Afterwards test, submit and, once working, comment properly.


/*===================================
                 Main               
===================================*/

int main()
{
    // Generate a random seed (for debugging)
    #if DEBUG_MODE
        srand(time(NULL));
    #endif

    // Create our pavilion and make sure it works
    pavilion p = pavilion_create();
    if (p == NULL)
        return 0;
    printf("Abertura pavilhao.\n");
        
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
            case 'L': docommand_L(p, command); break;
            case 'T': docommand_T(p, command); break;
            case 'S': docommand_S(p, command); break;
            case 'V': docommand_V(p, command); break;
            case 'Q': docommand_Q(p, command); break;
            case 'C': docommand_C(p); break;
            case 'P': docommand_P(p); break;
            case 'X': docommand_X(p); return;
            case '\n': break;
            default:  printf("Dados invalidos.\n"); break;
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
    int num_id=0, num_tax=0;
    char name[MAX_INPUT];

    // Ask for information (or generate some if debugging)
    #if !DEBUG_MODE
        sscanf(command, "E %d %d", &num_id, &num_tax);
        fgets(name, MAX_INPUT, stdin);
        // Remove the trailing \n
        name[strlen(name)-1]='\0';
    #else
        num_id = rand()%MAX_CLIENTS;
        num_tax = (int)rand();
        sprintf(name, "John Doe %d", num_id);
        printf("%d %d\n%s\n", num_id, num_tax, name);
    #endif

    // Check the data is good
    if (num_id <=0 || num_tax <= 0 || name[0] == '\0')
    {
        printf("Dados invalidos.\n");
        return;
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
    int num_id=0;
    client c;

    // Read the command and check if the client is valid
    if (sscanf(command, "F %d", &num_id) != 1)
    {
        printf("Visitante nao esta no pavilhao.\n");
        return;
    }
    if (num_id <= 0)
    {
        printf("Visitante nao esta no pavilhao.\n");
        return;
    }
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
        pavilion_move_client(p, num_id, LOCATION_QUEUE);
        printf("Chegada autorizada a fila.\n");
    }
}


/*===================================
             docommand_L
Add as many people as possible to the
      first empty trampolines
===================================*/

void docommand_L(pavilion p, char* command)
{
    // Variables
    int hours;
    int minutes;
    int timeminutes;
    int ret;

    // Read the command and check if the client is valid
    #if !DEBUG_MODE
        if (sscanf(command, "L %d:%d", &hours, &minutes) != 2)
        {
            printf("Dados invalidos.\n");
            return;
        }
    #else
        hours = 9;
        minutes = 0;
        printf("9:00\n");
    #endif

    // Check the data is good
    if (hours >= 24 || minutes >= 60)
    {
        printf("Dados invalidos.\n");
        return;
    }        

    // Calculate the time (in minutes)
    timeminutes = hours*60 + minutes;

    // Move the client
    ret = pavilion_move_client(p, timeminutes, LOCATION_TRAMPOLINE);
    if (ret == 0)
        printf("Fila vazia.\n");
    else if (ret == TRAMPOLINE_BUSY)
        printf("Trampolins ocupados.\n");
    else
        printf("Entrada de %d visitantes nos trampolins.\n", ret);
}


/*===================================
             docommand_T
  Print the client in the specified 
             trampoline
===================================*/

void docommand_T(pavilion p, char* command)
{
    // Variables
    int index;
    int ret;

    // Read the command and check if the client is valid
    if (sscanf(command, "T %d", &index) != 1)
    {
        printf("Dados invalidos.\n");
        return;
    }

    // Get the info
    ret = pavilion_get_trampoline_clientid(p, index);
    if (ret == TRAMPOLINE_EMPTY)
        printf("Trampolim vazio.\n");
    else if (ret == TRAMPOLINE_NULL)
        printf("Trampolim inexistente.\n");
    else
        printf("%s esta no trampolim %d.\n", client_get_name(pavilion_get_client(p, ret)), index);
}


/*===================================
             docommand_S
 Remove a client from the trampoline
===================================*/

void docommand_S(pavilion p, char* command)
{
    // Variables
    int num_id=0;
    int hours;
    int minutes;
    int timeminutes;

    // Read the command and check if the client is valid
    #if !DEBUG_MODE
        if (sscanf(command, "S %d %d:%d", &num_id, &hours, &minutes) != 3)
        {
            printf("Dados invalidos.\n");
            return;
        }        

    #else
        sscanf(command, "S %d", &num_id);
        hours = 10;
        minutes = 30;
        printf("10:30\n");
    #endif

    // Check the data given is valid
    if (num_id <= 0)
    {
        printf("Dados invalidos.\n");
        return;
    }

    // Check the client exists
    if (pavilion_exists_client(p, num_id) == FALSE)
    {
        printf("Visitante nao esta no pavilhao.\n");
        return;
    }
    client c = pavilion_get_client(p, num_id);

    // Calculate the time and make sure it makes sense
    timeminutes = hours*60 + minutes;
    if (client_get_time(c) >= timeminutes)
    {
        printf("Hora errada.\n");
        return;
    }

    // Move the client
    int ret = pavilion_move_client(p, num_id, LOCATION_BAR);
    if (ret == TRAMPOLINE_NULL)
        printf("Saida trampolim nao autorizada.\n");
    else 
    {
        printf("Saida trampolim autorizada.\n");
        client_set_bill(c, client_get_bill(c) + ((1+max(ceil((timeminutes - client_get_time(c)), 30)-1,0))*5));
        client_set_time(c, 0);
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
    char item[2];
    client c;

    // Read the command and make sure it's valid
    if (sscanf(command, "V %s %d %d", item, &amount, &num_id) != 3)
    {
        printf("Dados invalidos.\n");
        return;
    }
    if (amount <= 0 || num_id <=0)
    {
        printf("Dados invalidos.\n");
        return;
    }

    // Make sure we have a good variable read.
    item[0] = toupper(item[0]);
    item[1] = '\0';
    if (!pavilion_exists_food(p, item))
    {
        printf("Dados invalidos.\n");
        return;
    }

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
    else if (food_get_stock(pavilion_get_food(p, item)) < amount)
        printf("Produto %s esgotado.\n", item);
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
    if (sscanf(command, "Q %d", &num_id) != 1)
    {
        printf("Dados invalidos.\n");
        return;
    }        

    if (pavilion_exists_client(p, num_id) == FALSE)
    {
        printf("Visitante nao esta no pavilhao.\n");
        return;
    }
    c = pavilion_get_client(p, num_id);

    // Remove him from the pavilion
    if (client_get_location(c) != LOCATION_BAR)
        printf("Saida nao autorizada.\n");
    else
    {
        if (client_get_bill(c) == 0)
            bill = 5;
        else
            bill = client_get_bill(c);
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
        // Variables
        int i;
        int temp_keys[MAX_CLIENTS];
        char temp_name[MAX_CLIENTS][MAX_INPUT];

        // Fill our variables (and sort them)
        pavilion_sort_clients(p, temp_name, temp_keys);

        // Print the list of names
        for (i=0;i<pavilion_count_clients(p);i++)
        {
            printf("%s esta em ", temp_name[i]);
            switch(client_get_location(pavilion_get_client(p, temp_keys[i])))
            {
                case LOCATION_QUEUE:        printf("fila de trampolins.\n"); break;
                case LOCATION_TRAMPOLINE:   printf("trampolim %d.\n", pavilion_find_trampoline(p, temp_keys[i])); break;
                case LOCATION_BAR:          printf("bar.\n"); break;
            }
        }
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

    // Kick everyone out of the trampolines and pavilion, then print the money
    pavilion_close(p);
    printf("Caixa: %.2f euros.\n", pavilion_get_cash(p));

    // Go through all the food and print their stocks
    for (i=0;i<NUM_FOOD;i++)
    {
        char* key = food_get_key_from_index(i);
        food f = pavilion_get_food(p, key);
        if (f == NULL)
            continue;
        printf("Stock %s: %d.\n", food_get_name(f), food_get_stock(f));
    }
}