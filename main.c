#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Factorizes numbers from a file
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: (0) if successful, (1) if an error occurs
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: factors <file>\n");
		return (1);
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}

	char line[256];
	char command[300];

	while (fgets(line, sizeof(line), file))
	{
		line[strcspn(line, "\n")] = 0;

		snprintf(command, sizeof(command), "python3 factorize.py %s", line);
		system(command);
	}

	fclose(file);
	return (0);
}

