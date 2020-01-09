// Station with an S
// Main file
#include <fstream>
#include <iostream>
//#include "Stations.h"
#include <string>
#include <iomanip>
#include "stdlib.h"
//# Sec-b

namespace w2{

	enum PassType { PASS_STUDENT, PASS_ADULT, PASS_COUNT };
	//#define PASS_STUDENT 0;
	//#define PASS_ADULT 1;
	//#define PASS_COUNT 2;

	class Station{
		unsigned passes[PASS_COUNT];
		std::string name;
		std::string n;
		unsigned int s;
		unsigned int a;
		int index = 0;
	public:
		Station(){
		}
		Station(std::fstream& in){
			std::string line; // in = LINE (1x ROW = STRING;NUM NUM)
			getline(in, line);
			//std::cout << "line ->>" << line << "<<-\n";
			// 0 < 15-25
			while(index < line.size()){
				if(line[index] != ';')
					n += line[index];
				else
					break;
				index++;
			}
			// Built string "n" -- is line -> until delimiter ";", ++ SKIP ;
			//std::cout << "n=" << n << "<<-\n";
			
			if(index == line.size()){
				std::cerr << "missing ';' and pass cints in -->" << line << "<--\n";
				exit(10);
			} // Means no DELIMITER ";"
			index++; //?
			
			if(index > line.size()){
				std::cerr << "missing pass countsiin" << line <<"\n";
				exit(11);
			} // Somehow letter count is larger than original
			int num = 0;	//
			
			while (index < line.size()) { // While counting letters
				if (isdigit(line[index])) { // If is a DIGIT -> int NUM = 10*CURRENT + (ASCII) - NULL (convert)  - Increase by Base 10
					num = 10 * num + line[index] - '0';
				}
				else {
					break;
				}
				index++; //(Break from current loop and increment INDEX)
				if (index == line.size()) {
					std::cerr << "Mismatch of pair" << line << "\n";
					exit(12);
				}
			}
			s = num;
			//std::cout << "\n?CHAIN!1" << index << "\n";
			//std::cout << line[index];
			if (line[index] == ' ') {
				//std::cout << "TRUE!";
			}				
			else {
				std::cerr << "Error missing space \n";
				exit(13);
			}
			num = 0;
			index++;
			// CREATE S
			while (index < line.size()) {
				if (isdigit(line[index])) {
					num = 10 * num + line[index] - '0';
				}
				else {
					break;
				}
				index++;
				//std::cout << "num" << num << "\n";
			}
			a = num;
			//std::cout << "\n?CHAIN!2::" << index << "\n";
			//std::cout << line.size();
			if (index != line.size()) {
				std::cerr << "index not= linesize";
				exit(13);
			}
			else 
				//std::cout << "TRUE_2???\n"; // FIND A
			set(n, s, a); // CREATE STATION INSTANCE			
		}

		void set(const std::string& n, unsigned s, unsigned a){
			name = n;
			passes[PASS_STUDENT] = s;
	       	passes[PASS_ADULT] = a;		
	
		}
		void update(PassType pt, int value){
			passes[pt] += value;
		}
		unsigned inStock(PassType pt) const{
			return passes[pt];
		}
		const std::string& getName() const{
			return name;
		}
		void sales(){
			std::cout << getName() << "\n";
			int value;

			std::cout << " Student Passes sold : ";
			std::cin >> value;
			update(PASS_STUDENT, -value);

			std::cout << " Adult   Passes sold : ";
			std::cin >> value;
			update(PASS_ADULT, -value);
		}
		void restock(){
			std::cout << getName() << "\n";
			int value;

            std::cout << " Student Passes added : ";
            std::cin >> value;
            update(PASS_STUDENT, value);

            std::cout << " Adult   Passes added : ";
            std::cin >> value;
            update(PASS_ADULT, value);
		}
		void report(){
			// use <iomanip> to print this a/s table of columes
			std::cout << std::setw(18) << std::left << std::setfill(' ');
			std::cout << getName() << " ";
			std::cout << std::right;
			std::cout << std::setw(6) << inStock(PASS_STUDENT);
			//std::cout << (PASS_STUDENT);
			std::cout << std::setw(6) << inStock(PASS_ADULT);
			std::cout << "\n";
		}	
		void writeData(std::fstream& out2){
			out2 <<getName() << ';' 
				<< inStock(PASS_STUDENT) <<" "
				<< inStock(PASS_ADULT) << "\n";
		}

	};

	class Stations {
	private :
	        std::string dataFileName;
	        int stationCount;
			Station* stationTable = nullptr;
	       // unsigned int adu_pass[];       
	public :
		~Stations(){
			std::fstream out(dataFileName, std::ios::out | std::ios::trunc);
			if(out.is_open()){
				out << stationCount << ";\n";
				for(int s = 0; s < stationCount; s++){
                    stationTable[s].writeData(out);
            	}

				out.close();
			}
              	delete [] stationTable;
                //std::fstream out(dataFileName, std::ios::out);
                //putLine(out, Line);
                //out.close();
        }
	        Stations()
		{	
		}
	        Stations(char* filename)
		 : dataFileName(filename)
		{
			std::fstream in(filename, std::ios::in);
			if(! in.is_open()){
				std::cerr << "File inoperable" << filename << "\n";
				exit(1);
			}	
	
			std::string line;
			getline(in, line); //takes in a line
			//std::cout << "Line: " << line << "\n";
			
			int num = 0;
			int index = 0;
			while(index < line.size()){ // Move through line
				if( isdigit( line[index])){
					num = 10 * num + line[index] - '0'; // Assign num to index value, base 10
				}else
				break; // Cut While Loop

				index++; // position of line
			}
			//std::cout << "num === " << num << "\n";
			stationCount = num;	// station count = # row ------- first line
			//index++; // Next
			// expect semi colon (;)
			if(index < line.size()){
				if(line[index] != ';'){ // After first digit
					std::cerr << "expected ';' after station count, found "<< line[index] << "in ->>" << line << "<<- instead \n";
					exit(2);
				}
				//index++; //increase skip; row 1
				if(index >= line.size()){
					std::cerr << "extra characters after ';' in ->>>" << line << "<<<-\n";
		            exit(3);
				}
				//Gtg
				stationTable = new Station[stationCount]; // new Station created with the int StationCount (4)
				for(int s = 0; s < stationCount; s++){
					stationTable[s] = Station(in); // Next row, 4 times - CReate Object STATION
				}
			}else{
				std::cerr << "missing ';' after a station count in ->>>" << line << "<<<-\n";
				exit(4);
			}
		
			in.close();	
		}

		void update(){
			std::cout << "\nPasses Sold :\n";
                        std::cout << "------------\n";
                        for(int s= 0; s< stationCount; s++){
                                stationTable[s].sales();
                        }
		}
		void restock(){
			std::cout << "\nPasses Added :\n";  
                        std::cout << "--------------\n";  
                        for(int s= 0; s< stationCount; s++){
                                stationTable[s].restock();
                        }

		}
		void report(){
			std::cout << "\nPasses in Stock : Student Adult\n";
 			std::cout << "-------------------------------\n";
			for(int s= 0; s< stationCount; s++){		
				stationTable[s].report();
			} 		
		}
	

	};
}


