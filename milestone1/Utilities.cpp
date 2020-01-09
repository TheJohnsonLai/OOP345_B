#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include "Utilities.h"

char Utilities::delimiter = 0;
std::ofstream Utilities::logFile;

Utilities::Utilities(){
	field_width = 1;
}

size_t Utilities::getFieldWidth() const {
	return this -> field_width;
}

const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more) {
	more = false;

	std::string token;
	while (next_pos < str.size()) {
		if (str.at(next_pos) == delimiter) { 
			next_pos++;  
			more = true;
			break; 
		}
		if (str.at(next_pos) == '\0')
			more = false;
			break;
		token += str.at(next_pos);
		next_pos++;
	}

	while (*(token.begin()) == ' ')
		token.erase(token.begin());

	while (*(token.end() - 1) == ' ')
		token.erase(token.end() - 1);

	if (field_width < token.size())
		field_width = token.size();

	return token;
}

void Utilities::setDelimiter(const char newDelimiter) {
	Utilities::delimiter = newDelimiter;
}

void Utilities::setLogFile(const char* filename) {
	logFile.close();
	logFile.open(filename, logFile.out | logFile.trunc);
}


std::ofstream& Utilities::getLogFile() {
	return logFile;
}