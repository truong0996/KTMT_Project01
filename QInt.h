#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
//#pragma once

constexpr auto MAX_CAPACITY = 4;

class QInt
{
private:
	int arrBits[MAX_CAPACITY];			//This is what QInt actually is
public:
	QInt();
	~QInt();
	QInt(int x);
	QInt(std::string x);
	QInt operator~();
	QInt operator~() const;
	QInt& operator=(const QInt &x);
	QInt operator+(const QInt &x);
	QInt operator-(const QInt &x);
	bool operator<(const QInt &x);
	std::string toHexa();
	std::string toBin();
	friend QInt abs(QInt x);
	inline int getBit(int pos) const;
	inline int getBit(int pos);
	inline void toggleBit(int pos);
	std::string stringDiv2(std::string str);
	std::string toString();
	std::string squareString(int n);
	std::string addString(std::string a, std::string b);
};

//Hexadecimal represent in bit
const std::map<char, std::string> hexaRepMap = {
	{'0', "0000"},{'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"},
	{'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"},
	{'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
};