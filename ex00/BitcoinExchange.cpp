/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:54 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/27 14:27:51 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
//========================== DATE CLASS =========================//

Date::Date()
{
    
};
// Date::Date(std::string& year, std::string &month, std::string& day) :
// _year(std::atoi(year.c_str())),
// _month(std::atoi(month.c_str())),
// _day(std::atoi(day.c_str()))
// {
        
// };

Date::~Date()
{
    
};


Date::Date(const Date &other) : _year(other._year), 
                                _month(other._month),
                                _day(other._day)
{
    
};

Date & Date::operator=(const Date &other)
{
    if (this != &other)
    {
        _year = other._year;
        _month = other._month;
        _day = other._day;
    }
    return (*this);
}

bool Date::operator<(const Date& other) const
{
    if (_year != other._year) return _year < other._year;
    if (_month != other._month) return _month < other._month;
    return _day < other._day;
}


void Date::setDateField(const std::string &value, DateField dateField)
{
        std::istringstream iss(value);
    
        switch (dateField)
        {
            case YEAR:
                iss >> this->_year;
                if (iss.fail()) // think of checking values range here !!!!!!
                    throw std::invalid_argument("Invalid year: " + value);
                break;
            case MONTH:
                iss >> this->_month;
                if (iss.fail())
                    throw std::invalid_argument("Invalid month: " + value);
                break;
            case DAY:
                iss >> this->_day;
                if (iss.fail())
                    throw std::invalid_argument("Invalid day: " + value);
                break;
        }
}
const int& Date::getYear() const { return (this->_year); }
const int& Date::getMonth() const { return (this->_month); }
const int& Date::getDay() const { return (this->_day); }

std::ostream& operator<<(std::ostream &o,  const Date& date)
{
    std::cout << "=== Date OBJ content : ===" << std::endl;
    o   << "YEAR: "
        << date.getYear()
        << "\nMONTH: "
        << date.getMonth()
        << "\nDAY: "
        << date.getDay();

        return (o);
}

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

void BitcoinExchange::getInputData(std::string &file_name)
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
        {
            std::cout << "\n======= LINE ANALYSED: " << src_line << " ======= \n" << std::endl;
            extractDate(src_line);
        }
    }
    input_file.close();
}
void BitcoinExchange::extractDate(const std::string &data_line)
{
    std::string date_str, year_str, month_str, day_str, value_str;
    int nbBitcoins;
    
    date_str = data_line.substr(0, 10);
    if (date_str.size() != 10)
        throw std::logic_error("Invalid date entry: " + date_str);

    year_str = date_str.substr(0, 4);
    month_str = date_str.substr(5, 2);
    day_str = date_str.substr(8, 2);

    Date date;
    date.setDateField(year_str, Date::YEAR);
    date.setDateField(month_str, Date::MONTH);
    date.setDateField(day_str, Date::DAY);

    size_t pipe_pos = data_line.find('|');
    if (pipe_pos == std::string::npos)
        throw std::logic_error("No value separator '|' found in input line");

    value_str = data_line.substr(pipe_pos + 1);
    std::istringstream iss(value_str);
    iss >> nbBitcoins;

    _to_convert.insert(std::make_pair(date, nbBitcoins));
    printMapContent(_to_convert);
}

void BitcoinExchange::printMapContent(const std::map<Date, int> &map) const
{
    for (std::map<Date, int>::const_iterator it = map.begin(); it != map.end(); ++it)
    {
        std::cout << it->first << "\nBitcoins possessed at this date -> " << it->second << std::endl;    }
}
