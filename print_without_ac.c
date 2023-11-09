#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int i;
	int sum = 0;

	for (i = 0; av[i] != NULL; i++)
	{
		printf("av[%d]:%s\n", i, av[i]);
	}
	return (0);
}
