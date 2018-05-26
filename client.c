#include <stdlib.h>
#include "client.h"


/*===================================
           global variables
===================================*/

struct _client
{
    char*   name;
    void*   location;
    int     num_id;
	int     num_tax;
    int     time;
    float   bill;
};


/*===================================
           create_client
  Allocate memory for a new client
===================================*/

client create_client(int num_id, int num_tax, char* name)
{
    // Allocate memory
	client c = (client) malloc(sizeof(struct _client));

    // Check if not null
    if (c == NULL)
        return NULL;

    // Set all the necissary variables.
    c->name = name;
    c->num_id = num_id;
    c->num_tax = num_tax;
    c->location = NULL; // ***********************************CHANGE ME TO ENTER THE BAR
    c->time = 0;
    c->bill = 0;
	
    return c;
}


/*===================================
           destroy_client
 Free the memory associated with the
               client
===================================*/

int destroy_client(client c)
{
	int bill = c->bill;
	free(c);
	return bill;
}


/*===================================
             set_time
 Set the time the client entered the 
            trampoline
===================================*/

void set_time(client c, int t)
{
	c->time = t;
}


/*===================================
             set_bill
     Set the the clients' bill
===================================*/

void set_bill(client c, int cash)
{
	c->bill = cash;
}


/*===================================
             get_name
      Get the clients' name
===================================*/

char* get_name(client c)
{
	return(c->name);
}


/*===================================
             get_time
 Get the time the client entered the 
            trampoline
===================================*/

int get_time(client c)
{
	return(c->time);
}


/*===================================
             get_bill
      Get the clients' bill
===================================*/

int	get_bill(client c)
{
	return(c->bill);
}


/*===================================
            get_location
Get the clients' current location in
           the pavillion
===================================*/

void* get_location(client c)
{
	return(c->location);
}

/*===================================
            set_locatio
 Set's a new location for the client
         in the pavillion
===================================*/

void set_locatio(client c, void* localtion)
{
	c->location = location;
}

/*===================================
            add_to_bill
increases the client bill acording to
     his stay in the trampolins
===================================*/

int add_to_bill(client c)
{
	const int PAY_PERIOD = 30;
	const int PAY_PER_PERIOD = 5;
	int h, m, t, total_periods;
	scanf(" %d %d", h, m);
	t = h*60 + m - c->time;
	if(t%PAY_PERIOD)
		t = t + (PAY_PERIOD - t%PAY_PERIOD);	// round_up
	total_periods = t/30;
	c->bill = c->bill + total_periods*PAY_PER_PERIOD;
	c->time = 0;	// reset time in trampolines		
}
