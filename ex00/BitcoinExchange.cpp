/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:54 by jedusser          #+#    #+#             */
/*   Updated: 2025/06/02 13:55:05 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "colors.hpp"
#include "Date.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

//========================== BITCOIN_EXCHANGE CLASS =========================//

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _exchangeRates = other._exchangeRates;
    }
    return (*this);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) 
    : _exchangeRates(other._exchangeRates) {}

float BitcoinExchange::parseInputValue(const std::string &dataLine) const
{
    const std::string valueStr = dataLine.substr(12);
    
    float inputValue;
    std::istringstream iss(valueStr);
    iss >> inputValue;
    
    if (iss.fail())
        throw (std::invalid_argument("Error: invalid number format."));
    if (inputValue < 0)
        throw (std::invalid_argument("Error: not a positive number."));
    if (inputValue > 1000)
        throw (std::invalid_argument("Error: too large a number."));
        
    return (inputValue);
}

void BitcoinExchange::displayConversion(const Date &date, float amount, float rate) const
{
    std::cout << date << " => " << amount << " = " << amount * rate << std::endl;
}

void BitcoinExchange::processInputFile(const std::string &fileName)
{
    const std::string fullPath = fileName ;
    
    std::ifstream inputFile(fileName.c_str());
    if (!inputFile.is_open())
        throw (std::invalid_argument("Error: could not open file: " + fileName));

    std::string line;
    
    while (std::getline(inputFile >> std::ws, line))
    {
        if (line.empty())
            continue;
        if (line == "date | value")
            continue;
        try
        {
            Date inputDate;
            validateInputLine(line, inputDate);
            const float value = parseInputValue(line);
            const float rate = findClosestRate(inputDate);
            displayConversion(inputDate, value, rate);
        }
        catch(const std::exception& e)
        {
            std::cerr << RED << e.what() << RESET << '\n';
        }
    }
    inputFile.close();
}

float BitcoinExchange::findClosestRate(const Date &inputDate) const
{
    std::map<Date, float>::const_iterator it = _exchangeRates.find(inputDate);
    if (it != _exchangeRates.end())
        return (it->second);
    std::map<Date, float>::const_iterator upper = _exchangeRates.upper_bound(inputDate);
    if (upper == _exchangeRates.begin())
    {
        std::ostringstream oss;
        oss << "No available rate for date: " << inputDate;
        throw (std::runtime_error(oss.str())); 
    }
    --upper;
    return (upper->second);
}

void BitcoinExchange::validateInputLine(const std::string &dataLine, Date &inputDate) const
{
    if (dataLine.size() < 12 || dataLine.substr(10, 2) != " |")
        throw (std::invalid_argument("Error: bad input format => " + dataLine));
    
    const std::string dateStr = dataLine.substr(0, 10);
    const std::string yearStr = dateStr.substr(0, 4);
    const std::string monthStr = dateStr.substr(5, 2);
    const std::string dayStr = dateStr.substr(8, 2);

    validateDateField(dateStr, DATE);
    validateDateField(yearStr, YEAR);
    validateDateField(monthStr, MONTH);
    validateDateField(dayStr, DAY);

    inputDate.setDateField(yearStr, Date::YEAR);
    inputDate.setDateField(monthStr, Date::MONTH);
    inputDate.setDateField(dayStr, Date::DAY);
}

void BitcoinExchange::validateDateField(const std::string &value, DateFieldInput dateField) const
{
    std::istringstream iss(value);
    int val;
    
    switch (dateField)
    {
        case DATE:
            if (value.size() != 10 || value[4] != '-' || value[7] != '-')
                throw (std::invalid_argument("Error: invalid date format => " + value));
            break;

        case YEAR:
            iss >> val;
            if (iss.fail() || val < 1900 || val > 2100)
                throw (std::invalid_argument("Error: invalid year => " + value));
            break;
            
        case MONTH:
            iss >> val;
            if (iss.fail() || val < 1 || val > 12)
                throw (std::invalid_argument("Error: invalid month => " + value));
            break;
            
        case DAY:
            iss >> val;
            if (iss.fail() || val < 1)
                throw (std::invalid_argument("Error: invalid day => " + value));
            break;
    }
}

void BitcoinExchange::loadExchangeRates(const std::string &fileName)
{
    std::ifstream dataFile(fileName.c_str());
    if (!dataFile.is_open())
    {
        std::ostringstream errorMsg;
        errorMsg << "Error: could not open file: " << fileName;
        throw std::invalid_argument(errorMsg.str());
    }
    
    std::string line;
    
    while (std::getline(dataFile, line))
    {
        if (line.empty())
            continue;
        if (line == "date,exchange_rate")
            continue;
        try
        {
            processExchangeRateLine(line);
        }
        catch(const std::exception& e)
        {
            std::cerr << RED << e.what() << RESET << '\n';
        }
    }
    if (_exchangeRates.empty())
        throw (std::runtime_error("Error: no valid exchange rates found in file"));
    dataFile.close();
}

void BitcoinExchange::processExchangeRateLine(const std::string &dataLine)
{
    Date exchangeDate;
    
    try 
    {
        extractExchangeDate(exchangeDate, dataLine);
        const float value = extractExchangeValue(dataLine);
        _exchangeRates.insert(std::make_pair(exchangeDate, value));
    }
    catch (const std::exception& e)
    {
        throw;
    }
}

void BitcoinExchange::extractExchangeDate(Date &exchangeDate, const std::string &dataLine) const
{
    if (dataLine.size() < 10 || dataLine[4] != '-' || dataLine[7] != '-')
        throw (std::invalid_argument("Error: invalid date format in exchange data"));
    
    const std::string dateStr = dataLine.substr(0, 10);
    const std::string yearStr = dateStr.substr(0, 4);
    const std::string monthStr = dateStr.substr(5, 2);
    const std::string dayStr = dateStr.substr(8, 2);

    exchangeDate.setDateField(yearStr, Date::YEAR);
    exchangeDate.setDateField(monthStr, Date::MONTH);
    exchangeDate.setDateField(dayStr, Date::DAY);
}

float BitcoinExchange::extractExchangeValue(const std::string &dataLine) const
{
    const size_t commaPos = dataLine.find(',');
    if (commaPos == std::string::npos || commaPos + 1 >= dataLine.size())
        throw (std::invalid_argument("Error: invalid exchange rate format"));

    const std::string valueStr = dataLine.substr(commaPos + 1);
    
    float value;
    std::istringstream iss(valueStr);
    iss >> value;
    
    if (iss.fail() || value < 0)
        throw (std::invalid_argument("Error: invalid exchange rate value"));
        
    return (value);
}

const std::map<Date, float>& BitcoinExchange::getExchangeRates() const
{
    return( _exchangeRates);
}

void BitcoinExchange::printExchangeRates() const
{
    std::cout << "\n=== EXCHANGE RATES (" << _exchangeRates.size() << " entries) ===\n";
    
    for (std::map<Date, float>::const_iterator it = _exchangeRates.begin(); it != _exchangeRates.end(); ++it)
    {
        std::cout << "Date ["
                 << BLUE << it->first << RESET
                 << "] -> Rate: " 
                 << GREEN << it->second 
                 << RESET << std::endl;
    }
    std::cout << "=== END OF EXCHANGE RATES ===\n\n";
}