#include "miniRT.h"

void init_vector(t_vector *vec, int initial_capacity, int element_size)
{
	vec->data = malloc(initial_capacity * element_size);
	if (vec->data == NULL)
	{
		perror("Memory allocation failed\n");
		exit(1);
	}
	vec->size = 0;
	vec->capacity = initial_capacity;
	vec->element_size = element_size;
}

// Function to add an element to the end of the vector
void push_back(t_vector *vec, void *value)
{
	void *new_data;

	new_data = NULL;
	if (vec->size == vec->capacity)
	{
		new_data = malloc((vec->capacity + 1) * vec->element_size);
		if (new_data == NULL)
		{
			perror("Memory reallocation failed\n");
			exit(1);
		}
		vec->capacity++;
		memcpy(new_data, vec->data, vec->size * vec->element_size);
		free(vec->data);
		vec->data = new_data;
	}
	memcpy((char *)vec->data + vec->size * vec->element_size, value, vec->element_size);
	vec->size += 1;
}


void clear_vector(t_vector *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
}


// Function to access an element at a specific index
// int at(t_vector *vec, int index)
// {
// 	if (index < 0 || index >= vec->size)
// 	{
// 		perror("Index out of bounds\n");
// 		exit(1);
// 	}
// 	return vec->data[index];
// }
