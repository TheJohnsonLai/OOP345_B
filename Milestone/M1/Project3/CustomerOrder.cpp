#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Item.h"
#include "CustomerItem.h"

size_t CustomerOrder::field_width;

CustomerOrder::CustomerOrder(const std::string& cOrder) {
	nOrders = 0;
	order = nullptr;

	Utilities uObject;
	bool anyMore = true;
	size_t pos = 0;

	std::vector<std::string> token;

	for (int i = 0; anyMore; i++) {
		try {
			name = uObject.nextToken(cOrder, pos, anyMore);
		}
		catch (...) {
			throw std::string("name error");
		}

		if (pos >= cOrder.size()) { 
			anyMore = false;
		}

		try {
			product = uObject.nextToken(cOrder, pos, anyMore); 
		}
		catch (...) {
			throw std::string("product error");
		}

		while (anyMore) {
			token.push_back(uObject.nextToken(cOrder, pos, anyMore));
		}

		order = new CustomerItem[token.size()];
		for (int s = 0; s < token.size(); s++)
			order[s] = CustomerItem(token[s]);

		if (field_width < uObject.getFieldWidth())
			field_width = uObject.getFieldWidth();

		nOrders = token.size();

	}

}

CustomerOrder::CustomerOrder(CustomerOrder&& cOrder) NOEXCEPT {
	*this = std::move(cOrder);
}

CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& cOrder) NOEXCEPT {
	if (this != &cOrder) {
		delete[] order;

		order = cOrder.order;
		name = cOrder.name;
		product = cOrder.product;
		nOrders = cOrder.nOrders;

		cOrder.order = nullptr;
		cOrder.name = "";
		cOrder.product = "";
		cOrder.nOrders = 0;
	}

	return std::move(*this);
}

CustomerOrder::~CustomerOrder() {
	delete[] order;
}

unsigned int CustomerOrder::noOrders() const {
	return nOrders;
}

const std::string& CustomerOrder::operator[](unsigned int i) const {
	try {
		std::string referenceName;
		referenceName = order[i].getName();
	}
	catch (...) {
		throw std::string("Item index out of bounds");
	}

	return order[i].getName();
}

void CustomerOrder::fill(Item& item) {
	for (int i = 0; i < nOrders; i++) {
		if (order[i].asksFor(item)) {
			order[i].fill(item.getCode());
			item++;
		}
	}
}

void CustomerOrder::remove(Item& item) {
	for (int i = 0; i < nOrders; i++) {
		if (order[i].getName() == item.getName()) {
			nOrders -= 1;
		}
	}
}

bool CustomerOrder::empty() const {
	return (order == nullptr) ? true : false;
}

void CustomerOrder::display(std::ostream& os) const {
	os << std::setfill(' ') << std::setw(field_width) << std::left << name << " : " 
		<< product << std::endl;
	for (int i = 0; i < nOrders; i++) {
		order[i].display(os);
	}
}