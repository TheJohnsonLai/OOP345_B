#include <iostream>
#include "process.h"
#include "CString.h"
namespace w1{
	void process(char* s){
		//	std::cout << "process(" << s << "}\n";
	      	CString cs(s);
	     	//strncpy(str, s, MAX);
	       	//str[MAX] = '\0';
		std::cout << cs << "\n";
	}
}

