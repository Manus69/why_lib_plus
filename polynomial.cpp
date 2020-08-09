#include "why_lib.h"
#include <climits>

namespace why
{
    polynomial::polynomial(const std::vector<double>& coefficients)
    {
        this->coefficients = coefficients;
        this->degree = coefficients.size() - 1;
        this->domain = default_domain_bound;
    }

    polynomial::~polynomial(void)
    {
        ;
    }

    void polynomial::display(int precision) const
    {
        int n = this->degree;
        std::string string = "p(x) = ";

        while (n >= 0)
        {
            string.push_back('[');
            string += get_formatted_number_string(this->coefficients[n], precision);
            if (n > 1)
                string += "]x^" + std::to_string(n) + " + ";
            else if (n > 0)
                string += "]x + ";
            else if (n == 0)
                string += "]";
            n --;
        }
        std::printf("%s\n", string.c_str());
    }

    double polynomial::evaluate(double x) const
    {
        int n = this->degree;
        double current_term = 0;
        double value = 0;

        if (get_absolute_value(x) > this->domain)
            return not_in_set;
        while (n >= 0)
        {
            current_term = this->coefficients[n] * raise_to_power(x, n);
            value += current_term;
            if (value <= why::negative_infinty)
                return why::negative_infinty;
            else if (value >= why::infinity)
                return why::infinity;
            n --;            
        }
        return value;
    }

    polynomial get_derivative(const polynomial& polynomial)
    {
        std::vector<double> coefficients;
        double current_coefficient = 0;
        int n = 1;

        if (polynomial.degree == 0)
            return why::polynomial({0});
        while (n <= polynomial.degree)
        {
            current_coefficient = polynomial.coefficients[n] * n;
            coefficients.push_back(current_coefficient);
            n ++;
        }
        return why::polynomial(coefficients);
    }

    double find_root_in_the_interval(const polynomial& polynomial, double a, double b)
    {
        if (a > b)
            swap(a, b);
        
        double midpoint = not_in_set;
        double left_value = polynomial.evaluate(a);
        double right_value = polynomial.evaluate(b);
        double mid_value = not_in_set;

        if (get_absolute_value(left_value) < EPSILON)
            return left_value;
        if (get_absolute_value(right_value) < EPSILON)
            return right_value;
        while (b - a > DELTA)
        {
            midpoint = a + get_absolute_value((b - a) / 2);
            mid_value = polynomial.evaluate(midpoint);
            if (get_absolute_value(mid_value) < EPSILON)
                return midpoint;
            if (left_value < 0 && mid_value > 0)
            {
                b = midpoint;
                right_value = mid_value; 
            }
            else if (left_value > 0 && mid_value < 0)
            {
                b = midpoint;
                right_value = mid_value;
            }
            else if (mid_value < 0 && right_value > 0)
            {
                a = midpoint;
                left_value = mid_value;
            }
            else if (mid_value > 0 && right_value < 0)
            {
                a = midpoint;
                left_value = mid_value;
            }
            else
            {
                return not_in_set;
            }
        }
        return midpoint;
    }

    static void check_and_push(std::vector<double>& roots, double root)
    {
        if (root == not_in_set)
            return ;
        if (roots.size())
        {
            if (get_absolute_value(root - roots[roots.size() - 1]) < DELTA)
                return ;
        }
        roots.push_back(root);
    }

    std::vector<double> find_roots(const polynomial& polynomial)
    {
        double root = not_in_set;
        why::polynomial derivative;
        std::vector<double> critical_points;
        std::vector<double> roots;
        unsigned int n = 0;
        double a = 0;
        double b = 0;

        if (polynomial.degree == 0)
            return roots;
        if (polynomial.degree == 1)
        {
            root = solve_kxb(polynomial.coefficients[1], polynomial.coefficients[0]);
            if (root != not_in_set)
                roots.push_back(root);
            return roots;
        }
        derivative = get_derivative(polynomial);
        critical_points = find_roots(derivative);
        a = -polynomial.domain;
        while (n <= critical_points.size())
        {
            if (n == critical_points.size())
                b = polynomial.domain;
            else
                b = critical_points[n];
            root = find_root_in_the_interval(polynomial, a, b);
            check_and_push(roots, root);
            a = b + DELTA;
            n ++;
        }
        return roots;
    }

    void print_roots(std::vector<double> roots, int precision)
    {
        unsigned int n = 0;
        std::string string;

        if (!roots.size())
            std::printf("no real roots;");
        while (n < roots.size())
        {
            string = get_formatted_number_string(roots[n], precision);
            std::printf("%s; ", string.c_str());
            n ++;
        }
        std::printf("\n");
    }
}