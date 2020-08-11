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

    template <typename type>
    std::vector<type> concatenate_vectors(const std::vector<type>& lhs, const std::vector<type>& rhs)
    {
        unsigned int n = 0;
        std::vector<type> result;

        result.reserve(lhs.size() + rhs.size());
        while (n < lhs.size())
        {
            result.push_back(lhs[n]);
            n ++;
        }
        n = 0;
        while (n < rhs.size())
        {
            result.push_back(rhs[n]);
            n ++;
        }
        return result;
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

    template <typename type>
    type get_max_value(const std::vector<type>& vector)
    {
        unsigned int n = 0;
        type current_max;
        type current_value;

        if (!vector.size())
            throw -1; //this is terrible;
        current_max = get_absolute_value(vector[0]);
        while (n < vector.size())
        {
            current_value = get_absolute_value(vector[n]);
            if (vector[n] > current_max)
                current_max = current_value;
            n ++;
        }
        return current_max;
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
            void find_roots(void);
            friend polynomial get_derivative(const polynomial& polynomial);
            friend std::vector<double> find_roots(const polynomial& polynomial);
        private:
            int degree;
            bool roots_computed;
            double domain;
            std::vector<double> coefficients;
            std::vector<double> roots;
    };

    class matrix
    {
        private:
            std::vector<double> *entries;
            int number_of_rows;
            int number_of_columns;
            double largest_entry;
        public:
            matrix(std::string input);
            matrix(const std::vector<double>& entries, int n_rows);
            ~matrix(void);
            std::vector<double> get_row(int n) const;
            std::vector<double> get_column(int m) const;
            void display(int precision = 3) const;
            double operator() (int n, int m) const;
            friend double dot(const matrix& v, const matrix& w);
            friend matrix transpose(const matrix& A);
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

    matrix transpose(const matrix& A);
}


#endif