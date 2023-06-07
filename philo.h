#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef enum {
	THINKING,
	EATING,
	SLEEPING,
} philo_status;

typedef struct {
	pthread_mutex_t mutex;
} t_fork;

typedef struct s_data t_data;

typedef struct s_philo {
	t_fork 	*leftFork;
	t_fork 	*rightFork;
	int  	id;
	int  	eat_count;
	bool	done;
	philo_status status;
	t_data	*data;

	pthread_t thread;
} t_philo;

typedef struct s_data {
	t_philo	*philo;
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
} t_data;
