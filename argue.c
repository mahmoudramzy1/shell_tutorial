#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	printf("number of arguements is:%d\n", ac);
	int i;
	int sum = 0;

	for (i = 0; i < ac; i++)
	{
		printf("av[%d]:%s\n", i, av[i]);
		sum += atoi(av[i]);
	}
	printf("sum of av = %d\n", sum);
	return (0);
}
