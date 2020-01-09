#include <iostream>
#include <cstring>
#include "process.h"
#include "CString.h"
#include "w1.h"

using namespace w1;

int main(int c, char* v[]) {
	std::cout << "Command Line : ";
	int size = 0;
	for (int i = 0; i<c; i++) {
		std::cout << "v[" << i << "]" << v[i];
		size++;
	}

	cout << "Maximum number of characters stored : " << size;

	for (int i = 0; i<c; i++) {
		std::cout << i;
		process(v[i]);
	}

	std::cout << "Command Line : ";

	if (c == 1) {
		std::cout << "Insufficient number of arguments (min 1)\n";
		return 1;
	}

	return 0;
}
