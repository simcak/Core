#include <stdio.h>
#include <pthread.h>

#define RACE_CONDITION 100000
int             g_drinks_served;
pthread_mutex_t mutex;

void *serve_drink(void *arg)
{
	int	i;

	i = 0;
	while (i++ < RACE_CONDITION)
	{
		pthread_mutex_lock(&mutex); 
		g_drinks_served++;
		pthread_mutex_unlock(&mutex); 
	}
	return (NULL);
}
int main(void)
{
	pthread_t	waiter1;
	pthread_t	waiter2;

	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("Mutex initialization failed!\\n");
		return 1;
	}
	pthread_create(&waiter1, NULL, serve_drink, NULL);
	pthread_create(&waiter2, NULL, serve_drink, NULL);
	
	pthread_join(waiter1, NULL);
	pthread_join(waiter2, NULL);

	pthread_mutex_destroy(&mutex);
	printf("Total drinks served: %d\n", g_drinks_served);
	return (0);
}
