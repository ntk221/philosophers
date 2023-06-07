#include "philo.h"

bool		get_data(t_data *data, char *argv[]);
t_philo 	*create_philo(t_data *data);
void		print_philosophers(t_philo *philo, int num);

int main(int argc,  char *argv[]) {
	t_data	data;
	t_philo *philos;

	if (argc != 5 && argc != 6) 
	{
		printf("Error\n");
		return 1;
	}
	int num = atoi(argv[1]);
	if (num <= 0) 
	{
		printf("Error\n");
		return 1;
	}

	if (get_data(&data, argv) == false) 
	{
		free(data.philo);
		return (0);
	}

	printf("%d %d %d %d\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep);

	philos = create_philo(&data);
	
	print_philosophers(philos, data.philo_num);
	
	return 0;
}

bool	is_dead(t_philo *philo){return true;}
bool	is_done(t_philo *philo){return true;}

void	*philo_routine(void *arg) {
	t_philo *philo = (t_philo *)arg;

	while (!is_dead(philo) || !is_done(philo)) {
		// TODO: フォークの取得処理
		// TODO: 食事処理
		// TODO: スリープ処理
		// TODO: 思考処理
	}
	return NULL;
}

t_philo *create_philo(t_data *data)
{
	t_philo* philosophers;
    	t_fork forks[data->philo_num]; 

    	for (int i = 0; i < data->philo_num; i++) {
        	pthread_mutex_init(&forks[i].mutex, NULL);
    	}

	philosophers = malloc(sizeof(t_philo) * data->philo_num);
    	if (philosophers == NULL) {
		    printf("Error\n");
	    	exit(1);
    	}

    	for (int i = 0; i < data->philo_num; i++) {
        	t_philo *philo = &philosophers[i];
        	philo->leftFork = &forks[i];
		philo->rightFork = &forks[(i + 1) % data->philo_num];
		philo->id = i + 1; 
		philo->eat_count = 0; 
        	philo->done = false; 
        	philo->status = THINKING; 

		if (pthread_create(&philo->thread, NULL, philo_routine, philo) != 0) {
			printf("Error: failed to create thread");
			exit(1);
		}
	}
	
    	return philosophers;
}

void	print_philosophers(t_philo *philos, int num) {
	for (int i = 0; i < num; i++) {
		printf("philo->id: %d\n", philos[i].id);
		printf("philo->status: %d\n", philos[i].status == THINKING);
		printf("philo->status: %lu\n", (unsigned long)philos[i].thread);
	}
}

bool	get_data(t_data *data, char *argv[]) {
	
	data->philo_num = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);

	data->philo = malloc(sizeof(t_philo) *  data->philo_num);
	if (data->philo == NULL)
		return false;

	return true;
}
