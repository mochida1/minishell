#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
	char *buffer = NULL;

while (1)
	{
		buffer = readline("This is prompt: ");
		printf ("RL: >>%s<<\n", buffer);
		if (!strcmp(buffer, "exit"))
		{
			free (buffer);
			exit (0);
		}
		free (buffer);
	}
}
