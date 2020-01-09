#pragma once
#define __CSTRING_H__
using namespace std;
namespace w1{
	const int MAX = 3;
	class CString {
		char str[MAX + 1];
	public:
		CString(char* s);
		void display(std::ostream& os);
	};
}
ostream& operator<< (ostream& os, w1::CString& cs);
