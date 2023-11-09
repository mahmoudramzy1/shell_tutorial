#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL };
	pid_t child;
	int i;
	int status;


	for (i = 1; i <= 5; i++)
	{
		child = fork();
		if (child == -1)
		{
			perror("error:fork");
			exit(EXIT_FAILURE);
		}
	}
	if (child == 0)
	{
		if (execve("/usr/bin/ls", argv, NULL) == -1)
		{
			perror("error:execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	exit(EXIT_SUCCESS);
}
