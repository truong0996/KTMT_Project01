#include "QInt.h"

QInt::QInt() //Initialize 0 for arrBits
{
	for (int i = 0; i < MAX_CAPACITY; i++)
		arrBits[i] = 0;
}

QInt::~QInt()
{
}

QInt::QInt(int x)
{
	for (int i = 0; i < MAX_CAPACITY; i++)
		arrBits[i] = 0;

	this->arrBits[MAX_CAPACITY - 1] = std::abs(x);
	if (x < 0)
		*this = ~(*this) + 1; //change to two's complement
}

QInt::QInt(std::string x)
{
	for (int i = 0; i < MAX_CAPACITY; i++)
		arrBits[i] = 0;

	bool isNegative = false; //check sign
	if (x[0] == '-')
	{
		isNegative = true;
		x.erase(0, 1);
	}
	//delete 0 meaningless
	int i = 0;
	while (x[i] == '0' && x.length() > 1)
		i++;
	x.erase(0, i);
	i = 127; //128 bits
	// Convert decimal to binary
	while (x != "0")
	{
		int rm = (x[x.length() - 1] - '0') % 2;
		if (rm == 1)
		{
			this->toggleBit(i);
		}
		x = stringDiv2(x);
		i--;
	}
	if (isNegative)
		*this = ~(*this) + 1;
}

QInt::QInt(const QInt &x)
{
	for (int i = 0; i < MAX_CAPACITY; i++)
	{
		arrBits[i] = x.arrBits[i];
	}
}

// Set value method
QInt &QInt::operator=(const QInt &x)
{
	if (this == &x)
		return *this;
	for (int i = 0; i < MAX_CAPACITY; i++)
	{
		arrBits[i] = x.arrBits[i];
	}
	return *this;
}

// add 2 QInt
QInt QInt::operator+(const QInt &x)
{
	QInt rs;
	int temp = 0;
	unsigned int bit, xBit;
	for (int i = 127; i > 0; i--)
	{
		bit = this->getBit(i);
		xBit = x.getBit(i);
		switch (bit + xBit + temp)
		{
		case 3:
			temp = 1;
			rs.toggleBit(i);
			break;
		case 2:
			temp = 1;
			break;
		case 1:
			rs.toggleBit(i);
			temp = 0;
			break;
		}
	}
	return rs;
}

// subtract QInt ( + (-x))
QInt QInt::operator-(const QInt &x)
{
	QInt res;
	res = *this + 1 + (~x);
	return res;
}

bool QInt::operator==(const QInt &x)
{
	for (int i = 0; i < MAX_CAPACITY; i++)
	{
		if (this->arrBits[i] != x.arrBits[i])
			return false;
	}
	return true;
}

bool QInt::operator<(const QInt &x)
{
	QInt t = *this - x;
	int temp1 = (1 << 31) + 1;
	int temp2 = t.arrBits[0];
	int temp = temp1 & temp2;
	if (((1 << 31) + 1 & t.arrBits[0]) == 1)
		return true;
	return false;
}

bool QInt::operator>(const QInt &x)
{
	if (*this < x)
		return false;
	else if (*this == x)
		return false;
	return true;
}

bool QInt::operator>=(const QInt &x)
{
	if (*this < x)
		return false;
	return true;
}

bool QInt::operator<=(const QInt &x)
{
	if (*this > x)
		return false;
	return true;
}

// AND operator
QInt QInt::operator&(const QInt &x)
{
	QInt temp;
	for (int i = 0; i < MAX_CAPACITY; i++)
	{
		temp.arrBits[i] = this->arrBits[i] & x.arrBits[i];
	}
	return temp;
}
QInt QInt::operator&(int x)
{
	return this->operator&(QInt(x));
}

// OR operator
QInt QInt::operator|(const QInt &x)
{
	QInt temp;
	for (int i = 0; i < MAX_CAPACITY; i++)
	{
		temp.arrBits[i] = this->arrBits[i] | x.arrBits[i];
	}
	return temp;
}
QInt QInt::operator|(int x)
{
	return this->operator|(QInt(x));
}

// XOR operator
QInt QInt::operator^(const QInt &x)
{
	QInt temp;
	for (int i = 0; i < MAX_CAPACITY; i++)
	{
		temp.arrBits[i] = this->arrBits[i] ^ x.arrBits[i];
	}
	return temp;
}
QInt QInt::operator^(int x)
{
	return this->operator^(QInt(x));
}

// Shift left logic QInt
QInt QInt::operator<<(int x)
{
	if (x > 128)
		return *this;
	int quot = x / 32; //quotient
	int rm = x % 32;   //remainder
	QInt temp;
	if (quot > 0)
	{
		if (quot == 4) {
			*this = temp;
			return *this;
		}
		// shift left 32 bits / 1 quot unit
		for (int i = MAX_CAPACITY - 1 - quot; i >= 0; i--)
		{
			temp.arrBits[i] = this->arrBits[i + 1];
			*this = temp;
			return this->operator<<(rm);
		}
	}
	// store *this in temp
	temp = *this;
	// SHL x bits
	for (int i = MAX_CAPACITY - 1; i >= 0; i--)
	{
		this->arrBits[i] = this->arrBits[i] << x;
	}
	// SHL x bits lost in the above step
	for (int i = MAX_CAPACITY - 1; i > 0; i--)
	{
		for (int j = 0; j < x; j++)
		{
			int msb = (MAX_CAPACITY - i) * 32 - 1;
			
			bool bit_temp = temp.getBit(msb - j);
			if (bit_temp)
				this->toggleBit(msb + x - j);
		}
	}
	return *this;
}

// Bitwise operator not
QInt QInt::operator~()
{
	QInt t = *this;
	for (int i = 0; i < MAX_CAPACITY; i++)
		t.arrBits[i] = ~t.arrBits[i];
	return t;
}
QInt QInt::operator~() const
{
	QInt t = *this;
	for (int i = 0; i < MAX_CAPACITY; i++)
		t.arrBits[i] = ~t.arrBits[i];
	return t;
}

// absorb function
QInt abs(QInt x)
{
	QInt temp;
	if (x < temp)
		x = (~x) + 1;
	return x;
}

//Convert QInt to Hexadecimal
std::string QInt::toHexa()
{
	std::string result = "";
	//loop through arrBits[4]
	for (int i = MAX_CAPACITY - 1; i >= 0; i--)
	{
		int temp1 = arrBits[i];
		//temp2 save 4 bits that convert it into hexa
		char temp2 = 0;
		for (int j = 0, k = 0; j < 32; j++, k++)
		{								   //integer = 32 bits
			bool temp3 = (temp1 >> j) & 1; //get bit value at j pos

			//set temp3 bit value to temp2's k position
			if (temp3)
				temp2 = (1 << k) | temp2;
			else
				temp2 = ~(1 << k) & temp2;

			//hexadecimal represent
			if (k == 3)
			{
				temp2 += 48;	 //0..9 ascii code
				if (temp2 > '9') //A, B, ... F ascii code
					temp2 = temp2 + 'A' - '9' - 1;
				result.push_back(temp2);
				k = -1;
				temp2 = 0;
			}
		}
	}
	//Modify result
	//delete 0 bits
	for (int i = 0; i < result.length(); i++)
	{
		if (result[result.length() - i - 1] != '0')
		{
			break;
		}
		result.pop_back();
		i--;
	}
	//reverse
	std::reverse(result.begin(), result.end());
	return result;
}

//Convert QInt to Binary
std::string QInt::toBin()
{
	std::string result = "";
	//loop through arrBits[4]
	for (int i = MAX_CAPACITY - 1; i >= 0; i--)
	{
		int temp1 = arrBits[i];
		//loop through 32 bits because int = 4 bytes = 32 bits
		for (int j = 0; j < 32; j++)
		{
			char temp2 = (temp1 >> j) & 1; //get bit value at j pos
			temp2 += 48;
			result.push_back(temp2);
		}
	}
	//Modify result
	//delete 0 bits
	for (int i = 0; i < result.length(); i++)
	{
		if (result[result.length() - i - 1] != '0')
		{
			break;
		}
		result.pop_back();
		i--;
	}
	//reverse
	std::reverse(result.begin(), result.end());
	return result;
}

// get bit value at 'pos'th 
int QInt::getBit(int pos) const
{
	return (arrBits[pos / 32] >> (31 - pos % 32)) & 1;
}
int QInt::getBit(int pos)
{
	return (arrBits[pos / 32] >> (31 - pos % 32)) & 1;
}

// toggle bit value at 'pos'th
void QInt::toggleBit(int pos)
{
	this->arrBits[pos / 32] ^= (1 << (31 - pos % 32));
}

// divide by 2 for a large number string
std::string QInt::stringDiv2(std::string str)
{
	std::string temp;
	unsigned short int i = 0, j = 0, k = 0;
	if (str == "1")
		return "0";
	temp.resize(str.length());
	if (str[0] - 48 < 2)
	{
		i = 1;
		j = 10;
	}
	for (; i < str.length(); i++)
	{
		temp[k++] = (str[i] - 48 + j) / 2 + 48;
		j = ((str[i] - 48 + j) % 2) * 10;
	}
	temp.resize(k);
	return temp;
}

// to decimal representation
std::string QInt::toString()
{
	std::string result = "0";
	QInt temp = abs(*this);
	for (int i = 127; i > 0; i--)
	{
		int bit = temp.getBit(i);
		if (bit == 1)
		{
			std::string t = temp.squareString(127 - i); // 2^(i-1)
			result = temp.addString(result, t);			// + 2^(i-1)
		}
	}
	QInt _temp;
	if ((*this) < _temp)
		result.insert(0, "-");
	return result;
}

// squaring a number for n times
std::string QInt::squareString(int n)
{
	std::string result = "1";
	if (n == 0)
		return "1";
	for (int i = 0; i < n; i++)
	{
		result = addString(result, result);
	}
	return result;
}

// add 2 number (decimal type)
std::string QInt::addString(std::string a, std::string b)
{
	int alen = a.length();
	int blen = b.length();
	if (blen > alen)
	{
		std::string t = a;
		a = b;
		b = t;
		int tmp = alen;
		alen = blen;
		blen = tmp;
	}
	// make sure a > b
	char *c = new char[alen];
	int carry = 0; //carry a number if s is out of 10 unit
	for (int i = alen - 1; i >= 0; i--)
	{
		int lasta = a[i] - 48;
		int j = i - (alen - blen);
		int lastb;
		if (j < 0)
			lastb = 0;
		else
			lastb = b[j] - 48;

		int s = lasta + lastb + carry;
		if (s >= 10)
		{
			c[i] = s % 10 + 48;
			carry = 1;
		}
		else
		{
			c[i] = s + 48;
			carry = 0;
		}
	}

	if (carry == 1)
	{
		char *kq = new char[alen + 1];
		kq[0] = '1';
		for (int i = 0; i < alen; i++)
		{
			kq[i + 1] = c[i];
		}
		std::string rs(kq, alen + 1);
		return rs;
	}
	else
	{
		std::string rs(c, alen);
		return rs;
	}
}