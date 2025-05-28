/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:54 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/28 14:56:18 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "colors.hpp"
#include "Date.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

		
//========================== BITCOIN_EXCHANGE CLASS =========================//

BitcoinExchange::BitcoinExchange()
{
	
};

BitcoinExchange::~BitcoinExchange()
{
	
};

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_to_convert = other._to_convert;
	}
	return (*this);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _current_values(other._current_values) {};

void BitcoinExchange::getInputData(std::string &file_name)
{
	file_name.insert(0, "./");
	
	std::ifstream input_file(file_name.c_str(), std::ifstream::in);
	if (!input_file)
		throw(std::invalid_argument("Error: could not open file: "));
	std::string src_line;
	while (std::getline(input_file >> std::ws, src_line))
	{
		if (!src_line.empty() && src_line.compare("date | value"))
		{
			try
			{
				checkInputData(src_line);
				// storeInputData(src_line);
			}
			catch(const std::exception& e)
			{
				std::cerr << RED << e.what() << RESET << '\n';
			}
		}
	}
	input_file.close();
}

void BitcoinExchange::checkInputData(const std::string &data_line)
{
	Date inputDate;
	std::string date_str, 
				year_str, 
				month_str, 
				day_str,
				to_convert_str;

	
	date_str = data_line.substr(0, 10);
	to_convert_str = data_line.substr(12);
	year_str = date_str.substr(0, 4);
	month_str = date_str.substr(5, 2);
	day_str = date_str.substr(8, 2);

	
	checkInput(date_str, DATE);
	checkInput(to_convert_str, TO_CONVERT);
	checkInput(year_str, YEAR);
	checkInput(month_str, MONTH);
	checkInput(day_str, DAY);


	inputDate.setDateField(year_str, Date::YEAR);
	inputDate.setDateField(month_str, Date::MONTH);
	inputDate.setDateField(day_str, Date::DAY);
	
	std::cout << inputDate << std::endl;
}

void BitcoinExchange::checkInput(const std::string &value, DateFieldInput dateField)
{
	std::istringstream iss(value);
	std::string errorMsg;
	int val;
	
	switch (dateField)
	{
		case TO_CONVERT:
			iss >> val;
			
			if (iss.fail() || val < 0 || val > 1000)
			{
				if (val < 0)
					errorMsg = "Error: not a positive number.";
				if (val > 1000)
					errorMsg = "Error: too large a number.";
				throw std::invalid_argument(errorMsg);
			}
			break;
				
		case DATE:
			if (value.size() != 10)
				throw std::invalid_argument("Incomplete Date: " + value);
			break;

		case YEAR:
			iss >> val;
			if (iss.fail() || val < 1900 || val > 2100)
				throw std::invalid_argument("Invalid year: " + value);
			break;
			
		case MONTH:
			iss >> val;
			if (iss.fail() || val < 1 || val > 12)
				throw std::invalid_argument("Invalid month: " + value);
			break;
			
		case DAY:
			iss >> val;
			if (iss.fail() || val < 1)
				throw std::invalid_argument("Invalid day: " + value);
				
		int maxDays = 31;
		
		if (val == 2)
			maxDays = (val % 4 == 0 && (val % 100 != 0 || val % 400 == 0)) ? 29 : 28;
		else if (val == 4 || val == 6 || val == 9 || val == 11)
			maxDays = 30;
			
		if (val > maxDays)
		{
			throw std::invalid_argument("Day exceeds maximum for month");
			break;
		}
	}
}

void BitcoinExchange::getExchangeData(std::string &file_name)
{	
	std::ifstream data_file(file_name.c_str(), std::ifstream::in);
	if (!data_file)
	{
		std::ostringstream errorMsg;
		errorMsg << "File "
			<< file_name
			<< "Does not exists";
		throw(std::invalid_argument(errorMsg.str()));
	}
	std::string src_line;
	while (std::getline(data_file, src_line))
	{
		if (src_line.compare("date,exchange_rate"))
		{
			try
			{
				storeExchangeData(src_line);
			}
			catch(const std::exception& e)
			{
				std::cerr << RED << e.what() << RESET << '\n';
			}
		}
	}
	data_file.close();
}

void BitcoinExchange::storeExchangeData(const std::string &data_line)
{
	Date exchangeDate;
	float value;

	try 
	{
        extractExchangeDate(exchangeDate, data_line);
        extractExchangeValue(value, data_line);
		_current_values.insert(std::make_pair(exchangeDate, value));
    }
	catch (const std::exception& e)
	{
        throw;
    }
}


void BitcoinExchange::extractExchangeDate(Date &exchangeDate, const std::string &data_line)
{
	std::string date_str, 
				year_str, 
				month_str, 
				day_str;
	
	date_str = data_line.substr(0, 10);
	year_str = date_str.substr(0, 4);
	month_str = date_str.substr(5, 2);
	day_str = date_str.substr(8, 2);

	exchangeDate.setDateField(year_str, Date::YEAR);
	exchangeDate.setDateField(month_str, Date::MONTH);
	exchangeDate.setDateField(day_str, Date::DAY);
}

void BitcoinExchange::extractExchangeValue(float &value, const std::string &data_line)
{
	std::string value_str;

	size_t comma_pos = data_line.find(',');

	value_str = data_line.substr(comma_pos + 1);
	std::istringstream iss(value_str);
	iss >> value;
}

void BitcoinExchange::printMapContent(const std::map<Date, float> &map) const
{
    std::cout << "\n=== CSV CONTENTS (" << map.size() << " entries) ===\n";
	
    for (std::map<Date, float>::const_iterator it = map.begin(); it != map.end(); ++it)
    {
        std::cout	<< "Date [" 
					<< BLUE << it->first.getYear() << "-"
                 	<< it->first.getMonth() << "-" 
                 	<< it->first.getDay() 
                 	<< RESET << "] -> Value: " 
					<< GREEN << it->second 
					<< RESET << std::endl ;
    }
    std::cout << "=== END OF CSV CONTENTS ===\n\n";
}


const std::map<Date, float>& BitcoinExchange::getCurrentValue() const { return (this->_current_values); }
