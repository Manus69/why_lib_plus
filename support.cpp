#include "why_lib.h"

namespace why
{
    static int check_sequence_match(const std::string& haystack, const std::string& needle, int left_index)
    {
        int needle_length = needle.length();
        int haystack_length = haystack.length();
        int right_index = left_index + needle_length;
        int n = 0;

        if (!needle_length)
            return 0;
        if (!haystack_length)
            return -1;
        if (right_index > haystack_length)
            return -1;
        while (n < needle_length)
        {
            if (haystack[right_index - n - 1] != needle[needle_length - n - 1])
                return -1;
            n ++;
        }
        return left_index;
    }

    int get_index(const std::string& string, const char character)
    {
        int n = 0;
        int length = string.length();
        while (n < length)
        {
            if (string[n] == character)
                return n;
            n ++;
        }
        return -1;
    }

    int get_index(const std::string& haystack, const std::string& needle, int left_index, int right_index)
    {
        int n = left_index;
        int index_of_match = -1;
        right_index = (right_index == -1) ? haystack.length() - 1 : right_index;
        int true_right_index = right_index - needle.length() + 1;

        if (!haystack.length())
            return -1;
        if (!needle.length())
            return 0;
        if (left_index > true_right_index)
            return -1;
        while (n <= true_right_index)
        {
            if (haystack[n] == needle[0])
            {
                index_of_match = check_sequence_match(haystack, needle, n);
                if (index_of_match != -1)
                    return index_of_match;
            }
            n ++;
        }
        return index_of_match;
    }

    std::vector<std::string> split_string(const std::string& string, const std::string& separator)
    {
        std::vector<std::string> vector;
        std::string substring;
        int left_index = 0;
        int right_index = -1;
        int length = string.length();

        while (true)
        {
            right_index = get_index(string, separator, left_index, length - 1);
            if (right_index == -1)
            {
                substring = string.substr(left_index, length - 1);
                vector.push_back(substring);
                return vector;
            }
            else
            {
                substring = string.substr(left_index, right_index - left_index);
                vector.push_back(substring);
                left_index = right_index + 1;
            }
        }
        return vector;
    }

    static std::string get_fractional_part(double fractional_part, int precision)
    {
        int current_digit = 0;
        int n = 0;
        std::string number_string;

        while (n < precision)
        {
            fractional_part = fractional_part * 10;
            current_digit = (int)fractional_part;
            number_string.push_back(current_digit + '0');
            n ++;
            fractional_part = fractional_part - (int)fractional_part;
        }
        return number_string;
    }

    //no rounding - just truncation; valid range is int min - int max for now;
    std::string double_to_string(double x, int precision)
    {
        int integer_part = 0;
        double fractional_part = 0;
        std::string number_string;

        if (x < 0)
        {
            x = -x;
            number_string.push_back('-');
        }
        if (precision > MAX_PRECISION)
            precision = MAX_PRECISION;
        integer_part = (int)x;
        number_string += std::to_string(integer_part);
        fractional_part = x - integer_part;
        if (precision)
        {
            number_string.push_back('.');
            number_string += get_fractional_part(fractional_part, precision);
        }
        return number_string;
    }

    int round(double x)
    {
        int floor = 0;
        int ceiling = 0;
        double right_delta = 0;
        double left_delta = 0;

        if (x >= INT32_MAX)
            return INT32_MAX;
        else if (x <= INT32_MIN)
            return INT32_MIN;

        floor = (x < 0) ? (int)x - 1 : (int)x;
        ceiling = floor + 1;
        right_delta = ceiling - x;
        left_delta = x - floor;
        if (right_delta <= left_delta)
            return ceiling;
        return floor;
    }

    double raise_to_power(double x, int n)
    {
        double result = x;

        if (n == 0)
            return 1;
        if (n == 1)
            return x;
        while (n > 1)
        {
            result = result * x;
            if (result >= why::infinity)
                return why::infinity;
            else if (result <= why::negative_infinty)
                return why::negative_infinty;
            n --;
        }
        return result;
    }

    std::string get_formatted_number_string(double x, int precision)
    {
        int closest_int = round(x);
        double distance = get_absolute_value(x - closest_int);

        if (x == not_in_set)
            return std::string("not in set");

        if (distance < EPSILON)
            return std::to_string(closest_int);
        return double_to_string(x, precision);
    }

    double solve_kxb(double k, double b)
    {
        double x = not_in_set;

        if (k == 0 && b == 0)
            return 0;
        if (k == 0)
            return not_in_set;
        x = -(b / k);
        if (get_absolute_value(x) >= INT32_MAX)
            return not_in_set;
        return x;
    }
}