/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:54 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/26 15:12:00 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


Date::Date()
{
    
};

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

void Date::setDateField(const int &value, DateField dateField)
{
    if (dateField == YEAR)
        this->_year = value;
    if (dateField == MONTH)
        this->_month = value;
    if (dateField == DAY)
        this->_day = value;

}