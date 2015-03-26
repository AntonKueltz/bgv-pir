#include "Util.hpp"

namespace util{
    void generateDB(vector<vector<long> > & DB, unsigned long n, unsigned long l, long p){
        srand(time(0)); // seed the PRNG

        for(unsigned long rows = 0; rows < n; ++rows){
            vector<long> row;
            for(unsigned long bits = 0; bits < l; ++bits){
                row.push_back(rand() % p);
            }
            DB.push_back(row);
        }
    }

    void printVector(vector<long> v){
        for(unsigned long i = 0; i < v.size(); ++i)
            cout << v[i];
        cout << endl;
    }

    void printDB(vector<vector<long> > DB){
        cout << "\nDB is:" << endl;
        for(unsigned long rows = 0; rows < DB.size(); ++rows){
            printVector(DB[rows]);
        }
    }

    vector<long> circShiftRight(string s, unsigned long shift){
        vector<long> shifted;
        unsigned long slen = s.length();

        for(unsigned long i = 0; i < slen; ++i){
            unsigned long shiftIndex = (i + slen - shift) % slen;
            shifted.push_back(s[shiftIndex] == '1' ? 1 : 0);
        }

        return shifted;
    }

    vector<long> circShiftLeft(vector<long> v, unsigned long shift){
        vector<long> shifted;
        unsigned long slen = v.size();

        for(unsigned long i = 0; i < slen; ++i){
            unsigned long shiftIndex = (i + shift) % slen;
            shifted.push_back(v[shiftIndex]);
        }

        return shifted; 
    }
}