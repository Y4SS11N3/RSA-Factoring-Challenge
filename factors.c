#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void factorize_trial_division(mpz_t n, mpz_t factor) {
    mpz_t i;
    mpz_init_set_ui(i, 2); // Start division by 2

    // Trial division algorithm
    while (mpz_cmp_ui(n, 1) > 0) {
        if (mpz_divisible_p(n, i)) {
            mpz_divexact(factor, n, i); // n = n / i
            if (mpz_cmp(i, factor) <= 0) {
                mpz_clear(i);
                return;
            }
        }
        mpz_add_ui(i, i, 1); // Increment divisor
    }

    // If no factors found, set factor to n
    mpz_set(factor, n);
    mpz_clear(i);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./factors <file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    mpz_t n, factor, other_factor;

    while (getline(&line, &len, file) != -1) {
        mpz_init(n);
        mpz_init(factor);
        mpz_init(other_factor);
        
        mpz_set_str(n, line, 10); // Parse the number from the file
        
        // Factorize n using trial division
        factorize_trial_division(n, factor);
        
        mpz_cdiv_q(other_factor, n, factor); // n / factor

        if (mpz_cmp(factor, other_factor) > 0) {
            mpz_swap(factor, other_factor);
        }

        gmp_printf("%Zd=%Zd*%Zd\n", n, factor, other_factor);

        mpz_clear(n);
        mpz_clear(factor);
        mpz_clear(other_factor);
    }

    free(line);
    fclose(file);

    return 0;
}

