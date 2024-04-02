#include "miniRT.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

/**
 * Returns a random double between 0 and 1
*/
double	random_double()
{
	return (rand() / (RAND_MAX + 1.0));
}
/**
 * Returns a random double between min and max
*/
double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}
