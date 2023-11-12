#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int command_check(char *command)
{
	if (access(command, F_OK) == 0)
		printf("FILE FOUND\n");
	else
		printf("FILE NOT FOUND\n");
}
int main(void)
{
	char *buf = NULL;
	size_t n = 0;
	char *token;
	pid_t child;
	char *tokenArray[50];
	int i = 0;
	int status;

	while (1)
	{
		write(1, "#cisfun$ ", 9);
		getline(&buf, &n, stdin);
		while (buf == NULL)
		{
			write(1, "#cisfun$ ", 9);
			getline(&buf, &n, stdin);
		}
		token = strtok(buf, " \t\n");
		if (strcmp(token, "_which") == 0)
		{
			token = strtok(NULL, " \t\n");
			i = 0;
			while (token)
			{
				tokenArray[i] = token;
				i++;
				token = strtok(NULL, " \t\n");
			}
			tokenArray[i] = NULL;
			child = fork();
			if (child == 0)
				command_check(tokenArray[0]);
			if (child == -1)
				printf("fork error");
			else
				wait(&status);
		}
		else
		{
			child = fork();
			if (child == 0)
				printf("COMMAND NOT FOUND\n");
			if (child == -1)
				printf("command not found , fork error\n");
			else
				wait(&status);
		}
	}
	free(buf);
}
