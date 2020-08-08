#include "why_lib.h"

namespace why
{

    data_item::data_item(void *data, data_item::type type)
    {
        std::string *string_copy;

        if (type == data_item::integer)
            this->data.n = *(int *)data;
        else if (type == data_item::real)
            this->data.x = *(double *)data;
        else if (type == data_item::string)
        {
            string_copy = new std::string(*(std::string *)data);
            this->data.string = string_copy;
        }
        current_data_type = type;
    }

    data_item::~data_item(void)
    {
        if (current_data_type == data_item::string)
            delete data.string;
    }

    std::ostream& operator<< (std::ostream& stream, const data_item& item)
    {
        item.display();
        return stream;
    }

    void data_item::display(void) const
    {
        if (current_data_type == data_item::integer)
            std::printf("%d ", data.n);
        else if (current_data_type == data_item::real)
            std::printf("%.3f ", data.x);
        else if (current_data_type == data_item::string)
            std::printf("%s ", data.string->c_str());
        else
            std::printf("unknown data type\n");
    }

    void display_data_vector(const std::vector<data_item>& data_vector)
    {
        unsigned int n = 0;
        
        while (n < data_vector.size())
        {
            data_vector[n].display();
            n ++;
        }
        std::printf("\n");
    }

    data_item get_data_item(const std::string& string, data_item::type type)
    {
        int n = 0;
        double x = 0;

        if (type == data_item::integer)
        {
            n = std::atoi(string.c_str());
            return data_item(&n, type);
        }
        else if (type == data_item::real)
        {
            x = std::atof(string.c_str());
            return data_item(&x, type);
        }
        else if (type == data_item::string)
        {
            return data_item(new std::string(string), type);
        }
        else
            return data_item(0, data_item::unknown);
    }

    void get_data_vector
    (std::vector<data_item>& items, data_item::type type, const std::vector<std::string>& strings)
    {
        unsigned int n = 0;
        
        while (n < strings.size())
        {
            items.push_back(get_data_item(strings[n], type));
            n ++;
        }
    }
}
