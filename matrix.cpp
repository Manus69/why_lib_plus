#include "why_lib.h"

namespace why
{
    int check_matrix(const why::matrix& matrix)
    {
        ;
    }

    static int check_vector_uniformity(const std::vector<int>& vector)
    {
        unsigned int n = 0;
        int value = INT32_MAX;

        if (!vector.size())
            return 0;
        value = vector[0];
        while (n < vector.size())
        {
            if (vector[n] != value)
                return 0;
            n ++;
        }
        return 1;
    }
    matrix::matrix(std::string input)
    {
        std::vector<std::string> rows;
        std::vector<std::string> row_entries;
        std::vector<int> items_in_row;
        unsigned int j = 0;
        unsigned int k = 0;
        double current_entry = not_in_set;

        this->entries = new std::vector<double> ();
        this->largest_entry = 0;
        rows = why::split_string(input, ";");
        while (j < rows.size())
        {
            row_entries = why::split_string(rows[j], " ");
            items_in_row.push_back(0);
            k = 0;
            while (k < row_entries.size())
            {
                current_entry = std::atof(row_entries[k].c_str());
                if (get_absolute_value(current_entry) > this->largest_entry)
                    this->largest_entry = current_entry;
                (this->entries)->push_back(current_entry);
                items_in_row[j] ++;
                k ++;
            }
            j ++;
            row_entries.clear();
        }
        this->number_of_rows = j;
        if (check_vector_uniformity(items_in_row))
            this->number_of_columns = items_in_row[0];
        else
            exit(1); //error handling goes here
    }

    matrix::matrix(const std::vector<double>& entries, int n_rows)
    {
        if (entries.size() % n_rows != 0)
            exit(1); 
        this->entries = new std::vector<double> (entries);
        this->number_of_rows = n_rows;
        this->number_of_columns = entries.size() / n_rows;
        this->largest_entry = get_max_value(entries);
    }

    matrix::~matrix(void)
    {
        delete this->entries;
    }

    static std::string get_format_string(double largest_value, int precision)
    {
        int width = 0;
        std::string format;
        std::string entry = get_formatted_number_string(largest_value, precision);

        width = entry.size() + 1;
        format = "%-" + std::to_string(width) + "s";
        return format;
    }

    void matrix::display(int precision) const
    {
        int j = 0;
        int k = 0;
        std::string entry;
        std::string format;

        format = get_format_string(this->largest_entry, precision);
        while (j < this->number_of_rows)
        {
            k = 0;
            std::printf("|");
            while (k < this->number_of_columns)
            {
                entry = get_formatted_number_string((*this)(j, k), precision);
                // std::printf("%-5s ", entry.c_str());
                std::printf(format.c_str(), entry.c_str());
                k ++;
            }
            std::printf("|\n");
            j ++;
        }
    }

    inline double matrix::operator()(int j, int k) const
    {
        unsigned int index = j * number_of_columns + k;
        if (index < this->entries->size())
            return (*this->entries)[index];
        return not_in_set;
    }

    //dot is defined for row times column for now
    double dot(const matrix& v, const matrix& w)
    {
        int n = 0;
        double result = 0;

        if (v.number_of_rows != 1 || w.number_of_columns != 1)
            return not_in_set;
        if (v.number_of_columns != w.number_of_rows)
            return not_in_set;
        while (n < v.number_of_columns)
        {
            result += v(0, n) * w(n, 0);
            n ++;
        }
        return result;
    }

    std::vector<double> matrix::get_row(int n) const
    {
        std::vector<double> row;
        int left_index = 0;
        int right_index = 0;

        if (n > this->number_of_rows)
            return row;
        left_index = n * this->number_of_columns;
        right_index = left_index + this->number_of_columns;
        while (left_index <= right_index)
        {
            row.push_back((*this->entries)[left_index]);
            left_index ++;
        }
        return row;
    }

    std::vector<double> matrix::get_column(int m) const
    {
        std::vector<double> column;
        int index = 0;

        if (m > this->number_of_columns)
            return column;
        index = 0;
        while (index < this->number_of_rows)
        {
            column.push_back((*this)(index, m));
            index ++;
        }
        return column;
    }

    why::matrix transpose(const matrix& A)
    {
        std::vector<double> entries;
        std::vector<double> current_column;
        int n = 0;

        while (n < A.number_of_columns)
        {
            current_column = A.get_column(n);
            entries = concatenate_vectors(entries, current_column);
            current_column.clear();
            n ++;
        }
        return matrix(entries, A.number_of_columns);
    }
}