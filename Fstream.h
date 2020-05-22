#include "QInt.h"
#include <fstream>
using namespace std;

vector<string> readFile(ifstream &fin);
vector<string> calculate(vector<string> input);
string cal3Elements(vector<string> input);
string cal4Elements(vector<string> input);
vector<string> writeFile(fstream &fout);
void writeFile(ofstream &fout, vector<string> ans);
