#include "why_lib.h"
#include <complex>
#include <iostream>
#include <cstring>

void display_message_and_quit(const char *message)
{
    std::printf("%s\n", message);
    exit(1);
}

int main(int argc, char **argv)
{
    // char token_separator = ' ';
    // char  line_separator = '\n';
    // std::fstream file;
    // std::string line;
    // std::vector<std::string> token_vector;
    // std::vector<why::data_item> data_vector;

    // if (argc < 2 || argc > 4)
    //     display_message_and_quit("usage: [file] {c1, c2}\n");
    // file.open(argv[1]);
    // if (!file)
    //     display_message_and_quit("there is no file\n");
    // if (argc > 2 && (std::strlen(argv[2]) == 1))
    //     token_separator = *(argv[2]);
    // if (argc > 3 && (std::strlen(argv[3]) == 1))
    //     line_separator = *(argv[3]);
    // while (std::getline(file, line, line_separator))
    // {
    //     // std::printf("%s", line.c_str());
    //     token_vector = why::split_string(line, &token_separator);
    //     why::get_data_vector(data_vector, why::data_item::real, token_vector);
    //     why::display_data_vector(data_vector);
    //     data_vector.clear();
    // }


    why::matrix matrix = why::matrix("1 1 ; 0 1");
    matrix.display();
    why::matrix transpose = why::transpose(matrix);
    transpose.display();
    return 0;
}