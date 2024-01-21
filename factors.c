#include <stdio.h>
#include <gmp.h>

/**
 * factorize - Factorizes a number
 * @number: The number to factorize
 */
void factorize(mpz_t number)
{
	mpz_t i;
	mpz_init(i);

	for (mpz_set_ui(i, 2); mpz_cmp(i, number) <= 0; mpz_add_ui(i, i, 1))
	{
		if (mpz_divisible_p(number, i))
		{
			mpz_t quotient;
			mpz_init(quotient);

			mpz_divexact(quotient, number, i);
			gmp_printf("%Zd=%Zd*%Zd\n", number, quotient, i);
			mpz_clear(quotient);
			break;
		}
	}
	mpz_clear(i);
}

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

	mpz_t num;
	mpz_init(num);
	char line[1024];

	while (fgets(line, sizeof(line), file))
	{
		mpz_set_str(num, line, 10);
		factorize(num);
	}
	mpz_clear(num);
	fclose(file);
	return (0);
}

