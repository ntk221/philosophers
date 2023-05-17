#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef enum {
	THINKING,
	EATING,
	SLEEPING,
} philo_status;

typedef struct {
	pthread_mutex_t mutex;
} t_fork;

typedef struct {
	t_fork *leftFork;
	t_fork *rightFork;
	int  id;
	int  time_to_die;
	int  eat_count;
	philo_status status;
} t_philo;

int main(int argc,  char *argv[]) {
	if (argc != 5&& argc != 6) {
		printf("Error\n");
		return 1;
	}
	int num = atoi(argv[1]);
	if (num <= 0) {
		printf("Error\n");
		return 1;
	}

	return 0
}
