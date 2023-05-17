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
	t_fork 	*leftFork;
	t_fork 	*rightFork;
	int  	id;
	int  	eat_count;
	bool	done;
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

t_philo 	*create_philo(t_data *data);
void		print_philosophers(t_philo *philo, int num);

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

	t_philo *philos = create_philo(&data);
	
	print_philosophers(philos, data.philo_num);
	
	return 0;
}

t_philo *create_philo(t_data *data)
{
    int i;
    t_fork forks[PHILO_NUM]; 

    for (i = 0; i < PHILO_NUM; i++) {
        pthread_mutex_init(&forks[i].mutex, NULL);
    }

    t_philo* philosophers = malloc(sizeof(t_philo) * data->philo_num);
    if (philosophers == NULL) {
	    printf("Error\n");
	    exit(1);
    }

    for (i = 0; i < data->philo_num; i++) {
        t_philo *philo = &philosophers[i];
        philo->leftFork = &forks[i];
	philo->rightFork = &forks[(i + 1) % PHILO_NUM];
	philo->id = i + 1; 
	philo->eat_count = 0; 
        philo->done = false; 
        philo->status = THINKING; 
    }

    return philosophers;
}

void	print_philosophers(t_philo *philos, int num) {
	for (int i = 0; i < num; i++) {
		printf("philo->id: %d\n", philos[i].id);
		printf("philo->status: %d\n", philos[i].status == THINKING);
	}
}
