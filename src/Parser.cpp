/*
 * Parser.cpp
 *
 *  Created on: 19 jun 2024
 *      Author: Surface Pro 8 i7
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "Parser.h"

std::optional<JobShop> Parser::parse(std::string& filePath) {
	JobShop* js = new JobShop();
    std::ifstream file(filePath); // Open the file
    if (!file) { // Check if the file was successfully opened
        std::cerr << "Unable to open file: \"" << filePath << "\"" << std::endl;
		exit(1);
        JobShop* empty = new JobShop();
        return *empty; // Return an error code
    }
    std::string line;
    unsigned long lineNr = 0;
    unsigned long jobnr = 0;
    while (std::getline(file, line)) { // Read file line by line
    	if(lineNr == 0) {
    		//first is jobs // second is machines
    		std::vector<std::string> words = splitOnSpace(line);
			if(isNumeric(words.at(0))) {
				amountJobs = std::stoi(words.at(0));
			} else {
				std::cout << "ERROR on line " << lineNr+1 << "! Amount of jobs must be digit." << std::endl;
				exit(1);
			}
			if(isNumeric(words.at(1))) {
				amountMachines = std::stoi(words.at(1));
			} else {
				std::cout << "ERROR on line " << lineNr+1 << "! Amount of machines must be digit." << std::endl;
				exit(1);
			}
    	}
    	else {
    		Job j;
    		j.setId(lineNr-1);
    		std::vector<std::string> words = splitOnSpace(line);
    		int i = 0;
    		std::string id = "";
    		std::string duration = "";
    		for(std::string word : words) {
    			if(i % 2 == 0) {
    				id = word;
    			}
    			else {
    				duration = word;

    				if(isNumeric(id) && isNumeric(duration)) {
    					Task t(std::stoi(id),std::stoi(duration), jobnr);
        				j.addTask(t);
    				} else {
    					std::cout << "ERROR on line " << lineNr+1 << "! Input file contains other characters than digits" << std::endl;
    					exit(1);
    				}
    				id = "";
    				duration = "";
    			}
    			i++;
    		}
    		js->addJob(j);
    	}
    	lineNr++;
    	jobnr++;
    }
    if(jobnr - 1 != amountJobs) {
    	std::cout << "Syntax ERROR! Amount of jobs specified does not match parsed amount of jobs." << std::endl;
    }
    return *js;
}

bool Parser::isNumeric(const std::string& str) {
    for (char const &c : str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

std::vector<std::string> Parser::splitOnSpace(std::string& text) {
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) { // Extract words using operator >>
        words.push_back(word);
    }
    return words;
}

unsigned long Parser::getAmountMachines() {
	return amountMachines;
}
