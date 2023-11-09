#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *s = NULL;
	size_t n = 0;
	char *token;
	char **tokenArray;
	int status, i = 0;
	pid_t child_pid;
	/*int j;*/
	/*char *h[] = {"/usr/bin/ls", "-l", NULL};*/
	while (1)
	{
		write(1, "#cisfun$ ", 9);
		getline(&s, &n, stdin);
		token = strtok(s, "\t\n");
		tokenArray = malloc(sizeof(char *) * 1024);
		while (token)
		{
			tokenArray[i] = token;

			token = strtok(NULL, "\t\n");
			i++;
		}
		tokenArray[i] = NULL;
		child_pid = fork();
		if (child_pid == -1)
			perror("Error");
		if (child_pid == 0)
		{
			if (execve(tokenArray[0], tokenArray, NULL) == -1)
			{
				perror("error");
			}
		}
		else
		{
			wait(&status);
		}
	/*for (j = 0; tokenArray[j] != NULL; j++)
	{
		printf("%s", tokenArray[j]);
	}*/
		free(tokenArray);
		i = 0;
	}

}
