#include <stdio.h>

#include "../headers/primes.h"


int main() {

    printf(
            "╭---------------------------- BEGIN OF USAGE ----------------------------╮\n"
            "|     That very interesting program shows you all prime Mersenne numbers |\n"
            "| in segment [1; 2^31 - 1], i.e. it shows which Mersenne numbers from    |\n"
            "| first to 31-th are prime.                                              |\n"
            "|     So that you do not fall asleep in front of screen read an          |\n"
            "| interesting fact:                                                      |\n"
            "|     \"In September 2008, mathematicians at UCLA participating in GIMPS  |\n"
            "| for won part of a $100,000 prize from the Electronic Frontier          |\n"
            "| Foundation for their discovery of a very nearly 13-million-digit       |\n"
            "| Mersenne prime. The prize, finally confirmed in October 2009, is for   |\n"
            "| the first known prime with at least 10 million digits. The prime was   |\n"
            "| found on a Dell OptiPlex 745 on August 23, 2008. This was the eighth   |\n"
            "| Mersenne prime discovered at UCLA.\"                                    |\n"
            "╰---------------------------- END OF USAGE ------------------------------╯\n\n"
    );

    for (int i = 1; i < 32; ++i)
        if (is_prime((1 << i) - 1))
            printf("The %2d Mersenne number is prime: %d\n", i, (1 << i) - 1);

    return 0;
}