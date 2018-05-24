#ifndef _CLIENT
#define _CLIENT

	typedef struct _client * client;

	client	create_client(int num_id, int num_tax, char* name);
	int		destroy_client(client c);
	void	set_time(client c, int t);
	void	set_bill(client c, int cash);
	char*	get_name(client c);
	int		get_time(client c);
	int		get_bill(client c);
	void*	get_location(client c);

#endif