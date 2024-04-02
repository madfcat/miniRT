#include "miniRT.h"

t_interval	create_interval( double min, double max)
{
	t_interval	interval;

	interval.min = min;
	interval.max = max;
	return (interval);
}

void	set_interval(t_interval *interval, double min, double max)
{
	interval->min = min;
	interval->max = max;
}

bool	interval_contains(double x, t_interval interval)
{
	return (interval.min <= x && x <= interval.max);
}

bool	interval_surrounds(double x, t_interval interval)
{
	return (interval.min < x && x < interval.max);
}

double	clamp(double x, t_interval interval)
{
	if (x < interval.min)
		return (interval.min);
	if (x > interval.max)
		return (interval.max);
	return (x);
}

void	empty_interval(t_interval *interval)
{
	interval->min = INFINITY;
	interval->max = -INFINITY;
}

void	universe_interval(t_interval *interval)
{
	interval->min = -INFINITY;
	interval->max = INFINITY;
}
