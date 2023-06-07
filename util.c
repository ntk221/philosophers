#include "philo.h"
#include <sys/time.h>

long long timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 100 + tv.tv_usec / 1000);
}
