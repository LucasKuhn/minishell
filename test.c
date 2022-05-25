#include <stdio.h>

int add_one(int i)
{
	return(i + 1);
}

int function_receiving_function(int i, int(*f)(int))
{
	int new_i;

	new_i = f(i);
	return(new_i);
}

int main()
{
	int i;

	i = 1;
	printf("before: %i \n", i);
	i = function_receiving_function(i, &add_one);
	printf("after: %i \n", i);
}
