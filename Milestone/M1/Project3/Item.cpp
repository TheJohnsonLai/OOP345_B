#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Item.h"

size_t Item::field_width;


Item::Item(const std::string& item) {
	description = "No description";
	code = 1;

	Utilities uObject;
	bool anyMore = true;
	size_t pos = 0;
	std::string token;

	token = uObject.nextToken(item, pos, anyMore);
	if (pos == item.size()) { 
		anyMore = false;
	}

	if (field_width < uObject.getFieldWidth())
		field_width = uObject.getFieldWidth();


	try {
		if (anyMore) { 
			filler = uObject.nextToken(item, pos, anyMore); 
		}
		if (anyMore) { 
			remover = uObject.nextToken(item, pos, anyMore); 
		}
		if (anyMore) { 
			code = stoi(uObject.nextToken(item, pos, anyMore)); 
		}
		if (anyMore) { 
			description = uObject.nextToken(item, pos, anyMore); 
		}
	}
	catch (...) {
		throw std::string(item + " <-- *** no token found before the delimiter ***");
	}
}

bool Item::empty() const {
	return name == ""
		&& filler == ""
		&& remover == ""
		&& description == ""
		&& code == 1;
}

Item& Item::operator++(int ambiguous) {
	Item temp = *this;
	code++;
	return temp;
}

unsigned int Item::getCode() const {
	return code;
}

const std::string& Item::getName() const {
	return name;
}

const std::string& Item::getFiller() const {
	return filler;
}

const std::string& Item::getRemover() const {
	return remover;
}

void Item::display(std::ostream& os, bool full) const {

	os << std::setfill(' ');
	os << std::left << std::setw(field_width)
		<< name << " [" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << "] ";
		
	if (full) {
		os << "From " << std::left << std::setw(field_width) << filler << " To " << remover << std::endl
			<< std::left << std::setw(CODE_WIDTH + 1) << " : " << description;
	}

	os << std::endl;

}