/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:40:52 by jedusser          #+#    #+#             */
/*   Updated: 2025/06/02 13:46:08 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Date.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "colors.hpp"

//========================== DATE CLASS =========================//

Date::Date() : _year(0), _month(0), _day(0) {}

Date::~Date() {}

Date::Date(const Date &other) : _year(other._year), 
                               _month(other._month),
                               _day(other._day) {}

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

void Date::setDateField(const std::string &value, DateField dateField)
{
    std::istringstream iss(value);
    
    switch (dateField)
    {
        case YEAR:
            iss >> this->_year;
            break;
        case MONTH:
            iss >> this->_month;
            break;
        case DAY:
            iss >> this->_day;
            const int maxDays = getMaxDaysInMonth();
            if (this->_day > maxDays)
                throw (std::invalid_argument("Error: day exceeds maximum for month"));
            break;
    }
}

int Date::getMaxDaysInMonth() const
{
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (_month < 1 || _month > 12)
        return (0);
        
    if (_month == 2 && isLeapYear())
        return (29);
        
    return (daysInMonth[_month]);
}

bool Date::isLeapYear() const
{
    return (_year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0));
}

const int& Date::getYear() const { return _year; }
const int& Date::getMonth() const { return _month; }
const int& Date::getDay() const { return _day; }

bool Date::operator<(const Date& other) const
{
    if (_year < other._year)
        return true;
    if (_year > other._year)
        return false;
    if (_month < other._month)
        return true;
    if (_month > other._month)
        return false;
    return (_day < other._day);
}

bool Date::operator==(const Date& other) const
{
    return (_year == other._year && _month == other._month && _day == other._day);
}

std::ostream& operator<<(std::ostream& o, const Date& date)
{
    o << date.getYear() << '-' 
      << (date.getMonth() < 10 ? "0" : "") << date.getMonth() << '-'
      << (date.getDay() < 10 ? "0" : "") << date.getDay();
    return o;
}