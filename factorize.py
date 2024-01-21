import sys
import math


def factorize(number):
    for i in range(2, int(math.sqrt(number)) + 1):
        if number % i == 0:
            return number // i, i
    return number, 1


if __name__ == "__main__":
    num = int(sys.argv[1])
    factor1, factor2 = factorize(num)
    print(f"{num}={factor1}*{factor2}")
