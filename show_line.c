#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	printf("$ ");
	
	char *line = NULL;
	size_t len = 0;
	
	/*line = malloc(10);*/
	getline(&line, &len, stdin);
	printf("%s, %ld", line, len);

	free(line);
}
