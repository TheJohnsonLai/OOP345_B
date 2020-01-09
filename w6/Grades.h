//w6.h
#include <iostream>
#include <string>
#include <fstream>
#pragma once

namespace w6 {
	
	class Grades{
		
	private:
		std::string file;
		std::string* studentNum;
		double* grade;
		int count;
	
	public:
		Grades():studentNum(nullptr),grade(nullptr),count(0){
		}
		Grades(std::string fileName){
			try{
				std::fstream in(fileName, std::ios::in);
				if(in.is_open()){
					std::string line;
					while(getline(in, line)){
						count++;
					}
					in.clear();
					in.seekg(0);
					// allocate new array size
					studentNum = new std::string[count];
					grade = new double[count];
					for(int i = 0; i < count; i++){
						in >> studentNum[i];
						in >> grade[i];
						auto cr = studentNum[i].find('\r');
						if (cr != std::string::npos)
							studentNum[i].erase(cr);
					}
					in.close();
				}
				else {
					std::cerr << "Cannot open file" << fileName << "\n";
					exit(99);
				}
				
			}
			catch(std::fstream::failure fail){
				std::cerr << "File failed, error 1";
			}
		}
		template<typename F>//auto letter lambda expression
		void displayGrades(std::ostream& os, F f) const{
			
			for (int i = 0; i < count; i++){
				os << studentNum[i] << " " << grade[i] << " " << f(grade[i]) << "\n";
			}
		}
	};
}