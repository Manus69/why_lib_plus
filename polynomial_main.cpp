#include "why_lib.h"

void display_usage(void)
{
    std::printf("usage: ./polynomial c(n) c(n - 1) ... c(0)");
    exit(1);
}

//make a diy atof later?
int main(int argc, char **argv)
{
    std::vector<double> coefficients;
    std::vector<double> roots;
    int n = argc - 1;

    // std::printf("debug message\n");
    if (argc < 2)
        display_usage();
    while (n > 0)
    {
        coefficients.push_back(std::atof(argv[n]));
        n --;
    }
    why::polynomial polynomial = why::polynomial(coefficients);
    polynomial.display();
    // double x = why::find_root_in_the_interval(polynomial, -100, 0);
    // std::printf("%f\n", x);
    roots = why::find_roots(polynomial);
    why::print_roots(roots, 5);

    return 0;
}