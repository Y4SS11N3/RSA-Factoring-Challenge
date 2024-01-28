#include <stdio.h>
#include <gmp.h>

void factorize(mpz_t n, mpz_t factor) {
    mpz_t i;
    mpz_init_set_ui(i, 2);
    while (mpz_cmp(i, n) < 0) {
        if (mpz_divisible_p(n, i)) {
            mpz_set(factor, i);
            break;
        }
        mpz_add_ui(i, i, 1);
    }
    mpz_clear(i);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./factors <file>\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }
    char number_str[1024];
    mpz_t n, factor, product;
    mpz_init(n);
    mpz_init(factor);
    mpz_init(product);
    while (fgets(number_str, sizeof(number_str), file)) {
        mpz_set_str(n, number_str, 10);
        factorize(n, factor);
        mpz_tdiv_q(n, n, factor);
        mpz_mul(product, n, factor);
        gmp_printf("%Zd=%Zd*%Zd\n", product, factor, n);
    }
    mpz_clear(n);
    mpz_clear(factor);
    mpz_clear(product);
    fclose(file);
    return 0;
}

