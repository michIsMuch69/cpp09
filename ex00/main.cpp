/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:59 by jedusser          #+#    #+#             */
/*   Updated: 2025/06/02 13:54:24 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include "colors.hpp"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: <./first_ex> <input file>" << std::endl;
        return 1;
    }
    
    const std::string inputFileName = argv[1];
    const std::string dataFileName = "data.csv";
    
    BitcoinExchange bitcoinExchange;
    
    try 
    {
        bitcoinExchange.loadExchangeRates(dataFileName);
        bitcoinExchange.processInputFile(inputFileName);
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << e.what() << RESET << '\n';
    }
    
    return 0;
}