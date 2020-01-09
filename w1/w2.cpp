#include <iostream>
#include process.h
#include CString.h


using namespace std;

//const int MAX = 3;

char* strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

   for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';

   return dest;
}

namespace w1{
	const int MAX = 3;
	class CString{
		char str[MAX + 1]; // +1 for NULL

		public:
			CString(char* s){
				cout << "CString(" << s << ")\n";
				strncpy(str, s, MAX);
				str[MAX] = '\0';
			}
			void display(ostream& os){
				os << str;
			}
	};
}

ostream& operator<< (ostream& os, Cstring& cs){
	static int count = 0;
	os << count << ": ";
	cs.display(os);
	count++;

	return os;
}

void process(char* s){
	cout << "process(" << s << "}\n";
	CString cs(s);
	//strncpy(str, s, MAX);
	//str[MAX] = '\0';
	cout << cs;
}

int main(int c, char* v[]){
	cout << "Command Line : ";
	int size = 0;
   	for(int i=0; i<c; i++){
       		cout << "v[" << i << "]" << v[i];
   		size++;
	}

	cout << "Maximum number of characters stored : " << size;

	for(int i=0; i<c; i++){
		cout << i;
		process (v[i]);
	}

	cout << "Command Line : ";

	if(c == 1){
		cout << "Insufficient number of arguments (min 1)\n";
		return 1;
	}

	return 0;
}
