#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace w3{

	class Text {
		//private :
		size_t       s = 0;         // C++14
		std::string  *b = nullptr;  // C++14

	public:
		Text::~Text() // Destructor
		{
			delete[] b;
		}
		Text::Text() { // Default

		}
		/// COPY CONSTRUCTORS (2 + filename creation)
		Text(const Text& rhs)
		{
			*this = rhs;
		}
		Text::Text(char* filename) {
			std::fstream in(filename, std::ios::in);
			if (in.is_open()) { // Reading File
				std::string line; // create
				while (getline(in, line))
					s++;
				std::cout << "s=" << s << "\n";

				b = new std::string[s];

				in.clear(); // reset file error state from getline hitting EOF error state

				in.seekp(0); // Reset file reader to BEGINNING

				for (int i = 0; i < s; i++) {
					//b[i] += getline(in,line); // incorrect
					getline(in, b[i]);
					auto cr = b[i].find('\r');
					if (cr != std::string::npos)
						b[i].erase(cr);
				}

				in.close();
			}
			else {
				std::cerr << "Cannot open file" << filename << "\n";
				exit(99);
			}
		}
		Text& Text::operator=(const Text& rhs) {
			if (this != &rhs) {
				delete[] b;
				b = nullptr;
				s = 0;
			}
			if (rhs.b) {
				s = rhs.s;
				b = new std::string[s];

				for (int i = 0; i < s; i++) {
					b[i] = rhs.b[i];
				}
			}else{
				std::cout << "Ignored\n";
			}

			return *this;
		}
			// Moves ///////////////////////////////
		Text(Text&& rhs)
		{
			*this = std::move(rhs);
		}
		//Text::Text(Text&& filename){
		//	*this = std::move (rhs);
		//}
		Text&& Text::operator=(Text&& rhs) {
				if (this != &rhs) {
				// Delete brains
				delete[] b;
				// Turn rhs into zombie
				b = rhs.b; // Steal brain from rhs
				s = rhs.s; //
				rhs.b = nullptr; // turn rhs into zombie (transfer it)
				rhs.s = 0;
			}
			else {
				std::cout << "Move assignment operator: self assignment (ignored)\n";
			}
			return std::move(*this);
		}

		size_t size() const {
			return s;
		}

		};
} // namespace w3
