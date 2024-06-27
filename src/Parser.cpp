/*
 * Parser.cpp
 *
 *  Created on: 19 jun 2024
 *      Author: Surface Pro 8 i7
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub
}

JobShop& Parser::parse(std::string filePath) {
	JobShop* js = new JobShop();
    std::ifstream file(filePath); // Open the file
    if (!file) { // Check if the file was successfully opened
        std::cerr << "Unable to open file: \"" << filePath << "\"" << std::endl;
		exit(1);
        JobShop* empty = new JobShop();
        return *empty; // Return an error code
    }
    std::string line;
    int lineNr = 0;
    int jobnr = 0;
    while (std::getline(file, line)) { // Read file line by line
    	if(lineNr == 0) {
    		//first is jobs // second is machines
    		std::vector<std::string> words = this->splitOnSpace(line);
    		this->amountJobs = std::stoi(words.at(0));
    		this->amountMachines = std::stoi(words.at(1));
    	}
    	else {
    		Job j;
    		j.setId(lineNr-1);
    		std::vector<std::string> words = this->splitOnSpace(line);
    		int i = 0;
    		std::string id = "";
    		std::string duration = "";
    		for(std::string word : words) {
    			if(i % 2 == 0) {
    				id = word;
    			}
    			else {
    				duration = word;
    				Task t(std::stoi(id),std::stoi(duration), jobnr);
    				j.addTask(t);
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
    return *js;
}

std::vector<std::string> Parser::splitOnSpace(std::string text) {
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) { // Extract words using operator >>
        words.push_back(word);
    }
    return words;
}

unsigned long Parser::getAmountMachines() {
	return this->amountMachines;
}
