#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace util{
	void generateDB(vector<vector<long> > & DB, unsigned long n, unsigned long l, long p);
	void printVector(vector<long> v);
	void printDB(vector<vector<long> > DB);
	vector<long> circShiftRight(string s, unsigned long shift);
	vector<long> circShiftLeft(vector<long> v, unsigned long shift);
}