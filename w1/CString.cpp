//cstring
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "CString.h"
using namespace std;
char* strncpyy(char *dest, const char *src, size_t n)
{
    size_t i;
   for (i = 0; i < n; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';
   return dest;
}
namespace w1{
	//char str[MAX + 1]; // +1 for NULL
        CString::CString(char* s){
		//std::cout << "\n\nCString(" << s << ")\n\n";
		//std::cout << "STR== " << str << ") \n";
		std::strncpy(str, s, MAX);
		//std::cout << str << "!#13";
		str[MAX] = 0;
		//std::cout << "Success!!";
        }
        void CString::display(ostream& os){
                os << str;
        }
}
ostream& operator<< (ostream& os, w1::CString& cs) {
	static int count = 0;
	os << count << ": ";
	cs.display(os);
	count++;
	return os;
}

