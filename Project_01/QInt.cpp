#include "QInt.h"


QInt::QInt()	//Initialize 0 for arrBits
{
	for (int &i : arrBits)
		i = 1275236;
}


QInt::~QInt()
{
}

//Convert Binary to Hexadecimal
std::string QInt::binToHexa()
{
	std::string result = "";
	//loop through arrBits[4]
	for (int i = MAX_CAPACITY - 1; i >= 0; i--) {
		int temp1 = arrBits[i];
		//temp2 save 4 bits that convert it into hexa
		char temp2 = 0;
		for (int j = 0, k = 0; j < 32; j++, k++) {			 //integer = 32 bits
			bool temp3 = (temp1 >> j) & 1;						//get bit value at j pos

			//set temp3 bit value to temp2's k position
			if (temp3)
				temp2 = (1 << k) | temp2;
			else
				temp2 = ~(1 << k) & temp2;

			//hexadecimal represent
			if (k == 3) {
				temp2 += 48;
				if (temp2 > '9')
					temp2 = temp2 + 'A' - '9' - 1;
				result.push_back(temp2);
				k = -1;
				temp2 = 0;
			}
		}
	}
	//Modify result
	//delete 0 bits
	for (int i = 0; i < result.length(); i++) {
		if (result[result.length() - i - 1] != '0') {
			break;
		}
		result.pop_back();
		i--;
	}
	//reverse
	std::reverse(result.begin(), result.end());
	return result;
}

//Convert Hexadecimal to Binary
std::string QInt::hexaToBin() {
	return 0;
}