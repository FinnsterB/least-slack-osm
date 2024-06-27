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
	unsigned short amountJobs = 0;
	unsigned short amountMachines = 0;
public:
	Parser();
	JobShop& parse(std::string text);
	std::vector<std::string> splitOnSpace(std::string text);
	unsigned long getAmountMachines();
	virtual ~Parser() = default;
};

#endif /* PARSER_H_ */
