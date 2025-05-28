/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:59 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/28 14:54:00 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include "colors.hpp"


int main(int argc, char **argv)
{
    BitcoinExchange bitcoinExchange;
    
    if (argc != 2)
    {
        std::cout << "Usage: <./first_ex> <input file>" << std::endl;
        return (1);
    }
    std::string input_file_name = argv[1];
    std::string data_file_name = "./data.csv";
    try 
    {
        bitcoinExchange.getExchangeData(data_file_name);
        bitcoinExchange.printMapContent(bitcoinExchange.getCurrentValue());
        bitcoinExchange.getInputData(input_file_name);
    }
    catch (std::exception &e)
    {
        std::cerr << RED << e.what() << RESET << '\n';
    }
    return (0);
}