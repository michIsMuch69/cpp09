/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:59 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/27 11:37:32 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>


int main(int argc, char **argv)
{
    BitcoinExchange bitcoinExchange;
    
    if (argc != 2)
    {
        std::cout << "Usage: <./first_ex> <input file>" << std::endl;
        return (1);
    }
    std::string file_name = argv[1];
    try 
    {
        bitcoinExchange.getInputData(file_name);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    
    return (0);
}