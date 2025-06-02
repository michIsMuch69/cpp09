/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:50:56 by jedusser          #+#    #+#             */
/*   Updated: 2025/06/02 13:35:51 by jedusser         ###   ########.fr       */
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
    DAY
};

class BitcoinExchange
{
    private:
        std::map<Date, float> _exchangeRates;

        // Input file processing
        void validateInputLine(const std::string &dataLine, Date &date) const;
        void validateDateField(const std::string &value, DateFieldInput dateField) const;
        float parseInputValue(const std::string &dataLine) const;
        float findClosestRate(const Date &inputDate) const;
        
        // Exchange rate file processing
        void processExchangeRateLine(const std::string &dataLine);
        void extractExchangeDate(Date &date, const std::string &dataLine) const;
        float extractExchangeValue(const std::string &dataLine) const;

        // Output
        void displayConversion(const Date &date, float amount, float rate) const;

    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &);
        BitcoinExchange& operator=(const BitcoinExchange &);
        
        // Main functions
        void loadExchangeRates(const std::string &fileName);
        void processInputFile(const std::string &fileName);
        
        // Utility
        const std::map<Date, float>& getExchangeRates() const;
        void printExchangeRates() const;
};

std::ostream& operator<<(std::ostream &o, const Date& date);


#endif