#include "factors.h"

int factorize(mpz_t number) {
    mpz_t i;
    mpz_init_set_ui(i, 2); // Initialize 'i' to 2

    while (mpz_cmp(i, number) <= 0) {
        if (mpz_divisible_p(number, i)) { // Check if 'number' is divisible by 'i'
            mpz_t other_factor;
            mpz_init(other_factor);
            mpz_cdiv_q(other_factor, number, i); // other_factor = number / i

            gmp_printf("%Zd=%Zd*%Zd\n", number, i, other_factor);

            mpz_clear(other_factor);
            mpz_clear(i);
            return 1;
        }
        mpz_add_ui(i, i, 1); // i = i + 1
    }

    mpz_clear(i);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    mpz_t number;

    while ((read = getline(&line, &len, file)) != -1) {
        mpz_init_set_str(number, line, 10); // Initialize 'number' from string
        factorize(number);
        mpz_clear(number);
    }

    free(line);
    fclose(file);
    return 0;
}

