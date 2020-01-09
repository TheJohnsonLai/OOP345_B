// Workshop 6 - Lambda Expression
 // w6.cpp

 #include <iostream>
 #include "Grades.h"

 int main(int argc, char* argv[]) {
     if (argc != 2) {
         std::cerr << argv[0] <<
          ": incorrect number of arguments\n";
         std::cerr << "Usage: " << argv[0] << " file_name\n"; 
         return 1;
     }

		
         w6::Grades grades(argv[1]);
         // define the lambda expression for letter
		auto letter = [](double grade) -> std::string{
			if (grade >= 90.0){
				return "A+";
			}else if(grade >= 85.0){
				return "A";
			}else if(grade >= 80.0){
				return "A-";
			}else if(grade >= 77.0){
				return "B+";
			}else if(grade >= 73.0){
				return "B";			
			}else if(grade >= 70.0){
				return "B-";
			}else if(grade >= 67.0){
				return "C+";
			}else if(grade >= 63.0){
				return "C";
			}else if(grade >= 60.0){
				return "C-";
			}else if(grade >= 57.0){
				return "D+";
			}else if(grade >= 53.0){
				return "D";
			}else if(grade >= 50.0){
				return "D-";
			}else{
				return "F";
			}
		};




	 grades.displayGrades(std::cout, letter);




     std::cout << "Press any key to continue ... ";
     std::cin.get();
	 return 0;
 }