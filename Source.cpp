#include <iostream>
#include "Fstream.h"

using namespace std;

int main(int argc, char* argv[])
{
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	/*ifstream fin("input.txt");
	ofstream fout("output.txt");*/
	if (fin.is_open())
	{
		vector<string> input;
		vector<string> ans;
		input = readFile(fin);
		ans = calculate(input);
		writeFile(fout, ans);
	}
}