/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:56 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/27 14:07:19 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <map>
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

        void setDateField(const std::string &, DateField);
        const int& getYear() const;
        const int& getMonth() const;
        const int& getDay() const;
};


class BitcoinExchange
{
    private :
    
            std::map<Date, int> _to_convert;
            std::map<Date, int> _current_values;
    
        public :

            BitcoinExchange();
            // BitcoinExchange(std::string& year, std::string& month, std::string& day);
            ~BitcoinExchange();
            BitcoinExchange(const BitcoinExchange &);
            BitcoinExchange& operator=(const BitcoinExchange &);
            
            void getInputData(std::string &file_name);
            void extractDate(const std::string &data_line);
            void extractPossessed(const std::string &data_line);

            void printMapContent(const std::map<Date, int> &) const;
    


};

std::ostream& operator<<(std::ostream &o, const Date& date);


#endif