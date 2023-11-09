#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	char *str = "free palastine free aqsa";
	char delim[] = " ";
	char *stc = malloc(sizeof(char) * strlen(str) + 1);
	char *trunks;
	int i;

	strcpy(stc, str);
	trunks = strtok(stc, delim);
	while (trunks != NULL)
	{
		printf("%s\n", trunks);
		trunks = strtok(NULL, delim);
	}
	for (i = 0; i < 25; i++)
	{
		if (stc[i] == '\0')
			printf("\\0");
		else 
			printf("%c", stc[i]);
	}

	return (0);
}
