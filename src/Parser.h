/*
 * Parser.h
 *
 *  Created on: 19 jun 2024
 *      Author: Surface Pro 8 i7
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "JobShop.h"
#include <string>
class Parser {
private:
	unsigned long amountJobs = 0;
	unsigned long amountMachines = 0;
public:
	/**
	 * @brief Constructs a parser
	 * @return Parser
	 */
	Parser() = default;
	/**
	 * @brief checks if a given string is numeric
	 * @return true if numeric, false if not
	 * @param1 string to convert
	 */
	bool isNumeric(const std::string& str);
	/**
	 * @brief parses a given input
	 * @return parsed jobshop
	 * @param1 string to parse
	 */
	std::optional<JobShop> parse(std::string& text);
	/**
	 * @brief splits given string on spaces
	 * @return vector with splitted words
	 * @param1 string to split
	 */
	std::vector<std::string> splitOnSpace(std::string& text);
	unsigned long getAmountMachines();
	virtual ~Parser() = default;
};

#endif /* PARSER_H_ */
