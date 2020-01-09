#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace test {

	class ruleoffive {
	private:
	
	std::string *objC;
	size_t s = 0;
	
	public:
	
	ruleoffive::ruleoffive(){}
	ruleoffive::~ruleoffive(){
		delete objC;
	}
	
	ruleoffive::ruleoffive(const ruleoffive& rhs){
		*this = rhs;
	}
	
	ruleoffive& ruleoffive::operator=(const ruleoffive& rhs){
		if(this != &rhs){
			delete objC;
			objC = nullptr;
			s = 0;
		}
		if(rhs.objC){
			s = rhs.s;
			objC = new std::string[s];
			
			for(int i = 0; i < s; i++){
				objC[i] = rhs.objC[i];
			}
		else{
			std::cout << "Ignored\n";
		
		}		
		return *this;
		
	}
	
	ruleoffive::ruleoffive(ruleoffive&& rhs){
		*this = std::move(rhs); 
	}
	
	ruleoffive&& ruleoffive::operator=(ruleoffive&& rhs){}
		if(&&rhs != this){
			delete objC;			
			s = rhs.s;
			objC = rhs.objC;
			
			rhs.objC = nullptr;
			rhs.s = 0;
		}else{
			std::cout << "Failure\n";
		}
		
		return std::move(*this);
	};

}