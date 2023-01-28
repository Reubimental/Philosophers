#include <philosophers.h>

long long	current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

long long	time_diff(long long past, long long present)
{
	return (present - past);
}