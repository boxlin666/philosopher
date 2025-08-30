#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Global variable shared between threads
static long g_counter = 0;
// Mutex to protect the global counter
static pthread_mutex_t g_counter_lock;

// Function executed by the threads
void *thread_func(void *arg)
{
	long i;

	(void)arg; // Good practice to silent unused parameter warning
	i = 0;
	// Loop to increment the global counter
	while (i < 10000000)
	{
		// Lock the mutex before accessing the shared resource
		pthread_mutex_lock(&g_counter_lock);

		g_counter++; // This is the critical section

		// Unlock the mutex after accessing the shared resource
		pthread_mutex_unlock(&g_counter_lock);
		i++;
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1;
	pthread_t t2;

	// Initialize the mutex before using it
	if (pthread_mutex_init(&g_counter_lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		return (1);
	}
	// Create two threads that will run the same function
	if (pthread_create(&t1, NULL, thread_func, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, thread_func, NULL) != 0)
		return (1);
	// Wait for both threads to finish
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	// Destroy the mutex when it's no longer needed
	pthread_mutex_destroy(&g_counter_lock);
	// With the mutex, the final value will always be correct
	printf("Final counter value: %ld\n", g_counter);
	return (0);
}