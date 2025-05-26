/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:59 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/26 15:37:00 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

// void checkLine(const std::string &line)
// {
    
// }

void extractDate(const std::string &data_line)
{
    // check line...
    std::string date_part, year_part, month_part, day_part;

    date_part = data_line.substr(0, 10);

    year_part = date_part.substr(0, 4);

    // month_part = date_part.substr(5, 2);

    // day_part = date_part.substr(8, 2);

    // if (date_part.find()

    //if (substr 0-4 pas de - ou 5 a 7 pareil ou le reste)

    std::cout   << "extracted date_part : " 
                <<  date_part
                << std::endl;

    std::cout   << "extracted year_part : " 
                <<  year_part
                << std::endl;
    
    // std::cout   << "extracted month_part : " 
    //             <<  month_part
    //             << std::endl;
    
    // std::cout   << "extracted day_part : " 
    //             <<  day_part
    //             << std::endl;
    // Date *date = new Date();

    

    

    
}

void readInputFile(std::string &file_name)
{
    file_name.insert(0, "./");
    
    std::ifstream input_file(file_name.c_str(), std::ifstream::in);
    if (!input_file)
    {
        std::ostringstream oss;
        oss << "File "
            << file_name
            << "Does not exists";
        throw(std::logic_error(oss.str()));
    }
    std::string src_line;
    while (std::getline(input_file, src_line))
    {
        if (!src_line.empty() && src_line.compare("date | value"))
            extractDate(src_line);            
       std::cout << src_line << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: <./first_ex> <input file>" << std::endl;
        return (1);
    }
    std::string file_name = argv[1];
    try 
    {
        readInputFile(file_name);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    
    return (0);
}