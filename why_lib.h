#ifndef WHY_LIB_H
#define WHY_LIB_H

#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

#define EPSILON 1e-15
#define DELTA 1e-10
#define MAX_PRECISION 8
#define not_in_set (double)INT32_MAX + 1 //get a better name for this maybe? 

namespace why
{
    const double negative_infinty = (double)INT32_MIN - 1;
    const double infinity = (double)INT32_MAX + 1;

    template <typename Type>
    void swap(Type& x, Type& y)
    {
        Type store = x;
        x = y;
        y = store;
    }

    template <typename Type>
    void display_vector(const std::vector<Type>& vector)
    {
        unsigned int n = 0;

        while (n < vector.size())
        {
            std::cout << vector[n];
            std::cout << "\n";
            n ++;
        }
    }

    template <typename Type>
    inline Type get_absolute_value(Type a)
    {
        return (a < 0) ? -a : a;
    }

    union data
    {
        int n;
        double x;
        std::string *string;
    };

    class data_item
    {
        public:
            enum type
            {
                unknown, integer, real, string,
            };
            data_item(void *data, enum type type);
            ~data_item(void);

            inline enum type get_type(void) const
            {
                return current_data_type;
            }
            void display(void) const;
            friend std::ostream& operator<< (std::ostream& stream, data_item& item); //this is useless;

        private:
            union data data;
            enum type current_data_type;

    };

    class polynomial
    {
        static int const default_precision = 3;
        static double constexpr default_domain_bound = 128;
        public:
            polynomial(const std::vector<double>& coefficients = {});
            ~polynomial(void);

            void display(int precision = default_precision) const ;
            double evaluate(double x) const ;
            friend polynomial get_derivative(const polynomial& polynomial);
            friend std::vector<double> find_roots(const polynomial& polynomial);
        private:
            int degree;
            double domain;
            std::vector<double> coefficients;
    };

    int round(double x);
    double raise_to_power(double x, int n);
    int get_index(const std::string& string, const char character);
    int get_index
    (const std::string& haystack, const std::string& needle, int left_index = 0, int right_index = -1);
    std::vector<std::string> split_string(const std::string& string, const std::string& separator);
    data_item get_data_item(const std::string& string, data_item::type type);
    void get_data_vector
    (std::vector<data_item>& items, data_item::type type, const std::vector<std::string>& strings);
    void display_data_vector(const std::vector<data_item>& data_vector);
    std::string double_to_string(double x, int precision);
    std::string get_formatted_number_string(double x, int precision);
    double solve_kxb(double k, double b);

    polynomial get_derivative(const polynomial& polynomial);
    double find_root_in_the_interval(const polynomial& polynomial, double a, double b);
    std::vector<double> find_roots(const polynomial& polynomial);
    void print_roots(std::vector<double> roots, int precision);
}


#endif