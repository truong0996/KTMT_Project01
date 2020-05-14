#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
//#pragma once

constexpr auto MAX_CAPACITY = 4;;

class QInt
{
private:
	int arrBits[MAX_CAPACITY];			//This is what QInt actually is
public:
	QInt();
	~QInt();

	//Convert QInt to Hexadecimal
	std::string toHexa();
	//Convert QInt to Binary
	std::string toBin();

};

//Hexadecimal represent in bit
const std::map<char, std::string> hexaRepMap = {
	{'0', "0000"},{'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"},
	{'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"},
	{'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
};


