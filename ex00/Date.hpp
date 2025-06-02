/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:39:00 by jedusser          #+#    #+#             */
/*   Updated: 2025/06/02 13:58:44 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATE_HPP
#define DATE_HPP

#include <string>
#include <ostream>

class Date
{
    public:
        enum DateField
        {
            YEAR,
            MONTH,
            DAY
        };

        Date();
        ~Date();
        Date(const Date &);
        Date& operator=(const Date &);

        void setDateField(const std::string &value, DateField dateField);
        
        const int& getYear() const;
        const int& getMonth() const;
        const int& getDay() const;
        
        bool operator<(const Date& other) const;
        bool operator==(const Date& other) const;

    private:
        int _year;
        int _month;
        int _day;
        
        int getMaxDaysInMonth() const;
        bool isLeapYear() const;
};

std::ostream& operator<<(std::ostream& o, const Date& date);



#endif