#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

# define PHILO_NUM	5

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
	int  time_to_eat;
	int  time_to_sleep;
	int  eat_count;
	philo_status status;
} t_philo;

typedef struct {
	t_philo	*philo;
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
} t_data;

bool	get_data(t_data *data, char *argv[]) {
	
	data->philo = malloc(sizeof(t_philo) *  PHILO_NUM);
	if (data->philo == NULL)
		return false;

	data->philo_num = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	return true;
}



int main(int argc,  char *argv[]) {
	t_data	data;

	if (argc != 5&& argc != 6) {
		printf("Error\n");
		return 1;
	}
	int num = atoi(argv[1]);
	if (num <= 0) {
		printf("Error\n");
		return 1;
	}

	if (get_data(&data, argv) == false) {
		free(data.philo);
		return (0);
	}

	printf("%d %d %d %d\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep);
	

	return 0;
}

