/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:40:52 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/28 14:46:06 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Date.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "colors.hpp"

//========================== DATE CLASS =========================//

Date::Date(){};

Date::~Date(){};


Date::Date(const Date &other) : _year(other._year), 
								_month(other._month),
								_day(other._day) {};

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
			break;
	}
}
const int& Date::getYear() const { return (this->_year); }
const int& Date::getMonth() const { return (this->_month); }
const int& Date::getDay() const { return (this->_day); }

bool Date::operator<(const Date& other) const
{
	if (_year < other._year)
		return (true);
	if (_year > other._year)
		return (false);
	if (_month < other._month)
		return (true);
	if (_month > other._month)
		return (false);
	return (_day < other._day);
}

bool Date::operator==(const Date& other) const
{
	return (_year == other._year && _month == other._month && _day == other._day);
}

std::ostream& operator<<(std::ostream& o, const Date& date)
{
    o << date.getYear() << '/' << date.getMonth() << '/' << date.getDay();
    return o;
}