#include "Fstream.h"

vector<string> readFile(ifstream &fin)
{
	
	vector<string> input;
	while (!fin.eof())
	{
		string temp;
		getline(fin, temp);
		input.push_back(temp);
	}
	return input;
}

vector<string> calculate(vector<string> input)
{
	vector<string> res;
	int n = input.size();
	for (int i = 0; i < n; i++)
	{
		vector <string> temp;
		string temp1 = input[i];
		string temp2 = "";
		for (int j = 0; j < temp1.length(); j++)
		{
			if (temp1[j] != ' ')
				temp2 += temp1[j];
			else
			{
				temp.push_back(temp2);
				temp2 = "";
			}
		}
		temp.push_back(temp2);
		if (temp.size() == 3)
			res.push_back(cal3Elements(temp));
		else if (temp.size() == 4)
			res.push_back(cal4Elements(temp));
	}
	return res;
}

string cal3Elements(vector<string> input)
{
	QInt ans;
	QInt a;
	int he;

	string temp = input[0];

	if (temp == "2")
	{
		a.readBinString(input[2]);
		he = 2;
	}
	else if (temp == "10")
	{
		QInt b(input[2]);
		a = b;
		he = 10;
	}
	else if (temp == "16")
	{
		a.readHexString(input[2]);
		he = 16;
	}

	temp = input[1];

	if (temp == "~")
		ans = ~a;
	else if (temp == "ror")
		ans = a.ror();
	else if (temp == "rol")
		ans = a.rol();
	if(temp == "2")
		return a.toBinString();
	if(temp == "10")
		return a.toString();
	if(temp == "16")
		return a.toHexaString();

	if (he == 2 || temp == "2")
		return ans.toBinString();
	else if (he == 10 || temp == "10")
		return ans.toString();
	else if (he == 16 || temp == "16")
		return ans.toHexaString();
}

string cal4Elements(vector<string> input)
{
	QInt ans;
	QInt a;
	QInt b;
	int he;

	string temp = input[0];

	if (temp == "2")
	{
		a.readBinString(input[1]);
		b.readBinString(input[3]);
		he = 2;
	}
	else if (temp == "10")
	{
		QInt c(input[1]);
		QInt d(input[3]);
		a = c;
		b = d;
		he = 10;
	}
	else if (temp == "16")
	{
		a.readHexString(input[1]);
		b.readHexString(input[3]);
		he = 16;
	}
	
	temp = input[2];
	if (temp == "+")
		ans = a + b;
	else if (temp == "-")
		ans = a - b;
	else if (temp == "*")
		ans = a * b;
	else if (temp == "/")
		ans = a / b;
	else if (temp == "|")
		ans = a | b;
	else if (temp == "&")
		ans = a & b;
	else if (temp == "^")
		ans = a ^ b;
	else if (temp == "<<")
		ans = a << stoi(input[3]);
	else if (temp == ">>")
		ans = a >> stoi(input[3]);
	

	if (he == 2)
		return ans.toBinString();
	else if (he == 10)
		return ans.toString();
	else if (he == 16)
		return ans.toHexaString();
}

void writeFile(ofstream &fout, vector<string> ans)
{
	for (int i = 0; i < ans.size(); i++)
	{
		fout << ans[i] << endl;
	}
}