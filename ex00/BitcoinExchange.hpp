/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:56 by jedusser          #+#    #+#             */
/*   Updated: 2025/05/28 14:09:01 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <map>
#include <string>
#include "Date.hpp"

enum DateFieldInput
{
    DATE,
    YEAR,
    MONTH,
    DAY,
    TO_CONVERT
};

class BitcoinExchange
{
    private :
    
            std::multimap<Date, float> _to_convert;
            std::map<Date, float> _current_values;
    
        public :

            BitcoinExchange();
            ~BitcoinExchange();
            BitcoinExchange(const BitcoinExchange &);
            BitcoinExchange& operator=(const BitcoinExchange &);
            
            void getInputData(std::string &file_name);
            void checkInputData(const std::string &data_line);
            void checkInput(const std::string &value, DateFieldInput dateField);

            void getExchangeData(std::string &file_name);
            void storeExchangeData(const std::string &data_line);
            void extractExchangeDate(Date &date, const std::string &data_line);
            void extractExchangeValue(float &nbBitcoins, const std::string &data_line);

            const std::map<Date, float>& getCurrentValue() const;
            void printMapContent(const std::map<Date, float> &) const;
};

std::ostream& operator<<(std::ostream &o, const Date& date);


#endif