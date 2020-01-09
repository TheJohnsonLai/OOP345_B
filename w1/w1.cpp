#include <iostream>
#include <cstring>
#include "process.h"
#include "CString.h"
using namespace std;
using namespace w1;
//const int MAX = 3;
int main(int argc, char* argv[]){
	std::cout << "Command Line :";
   	for(int i=0; i<argc; i++){
       		cout << " " << argv[i];
	}
	cout << "\nMaximum number of characters stored : " << MAX << "\n";
	if(argc <= 1){
                cout << "Insufficient number of arguments (min 1)\n";
                return 1;
        }
	for(int i=1; i<argc; i++){
		//cout << (i-1) << ": ss";
		w1::process (argv[i]);
	}
	//cout << "Command Line : " << (argv[0]) << "\n";

	return 0;
}
//("w1 oop345 btp131");
