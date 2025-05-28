/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:39:00 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/28 14:23:34 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATE_HPP
#define DATE_HPP

#include <string>

class Date
{
    private :
    
        int _year;
        int _month;
        int _day;

    public :
    
        enum DateField
        {
            YEAR,
            MONTH,
            DAY
        };
        Date();
        // Date(std::string& year, std::string& month, std::string& day);
        ~Date();
        Date(const Date &);
        Date& operator=(const Date &);
        bool operator<(const Date&) const ;
        bool operator==(const Date&) const ;

        void setDateField(const std::string &, DateField);
        const int& getYear() const;
        const int& getMonth() const;
        const int& getDay() const;
};



#endif