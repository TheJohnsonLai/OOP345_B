#include <iostream>
#include <iomanip>
#include <string>
#include "Item.h"
#include "CustomerItem.h"

CustomerItem::CustomerItem(const std::string& customerItem) {
	name = customerItem;
	filled = false;
	code = 0;
}

bool CustomerItem::asksFor(const Item& item) const {
	return (name == item.getName());
}

bool CustomerItem::isFilled() const {
	return filled;
}

void CustomerItem::fill(const unsigned int fillIt) {
	code = fillIt;
	filled = true;
}

void CustomerItem::clear() {
	code = 0;
	filled = false;
}

const std::string& CustomerItem::getName() const {
	return name;
}

void CustomerItem::display(std::ostream& os) const {

	(isFilled()) ? os << " + " : os << " - ";
	os << " [" << std::setw(CODE_WIDTH) << std::setfill('0') << std::right << code << "] " 
		<< name << std::endl;

}