#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>

// HElib files
#include "FHE.h"
#include "FHEContext.h"
#include "EncryptedArray.h"

// NTL files
#include <NTL/lzz_pXFactoring.h>

// My files
#include "FoldingTree.hpp"
#include "PIRClient.hpp"
#include "PIRServer.hpp"
#include "Util.hpp"

#define DEBUG true
#define FOLD  false
#define TIMED true

using namespace std;

FHEcontext initBGV(long p){
                 // p is the plaintext base [default=2]
    long r = 1;  // r is the lifting [default=1]
    long d = 1;  // d is the degree of the field extension [default==1]
                 // (d == 0 => factors[0] defined the extension)
    long c = 2;  // c is number of columns in the key-switching matrices [default=2]
    long k = 80; // k is the security parameter [default=80]
    long L = 4;  // L is the # of primes in the modulus chain [default=4*R]
    long s = 0;  // s is the minimum number of slots [default=4]

    // WTF HOW DOES M WORK SOMEONE EXPLAIN
    // I THOUGHT d = phi(m) / l WHERE l = slots??????
    long m = FindM(k, L, c, p, d, s, 0); // 1003

    vector<long> a, b;
    FHEcontext context(m, p, r, a, b);
    buildModChain(context, L, c);
    return context;
}

int main(int argc, char * argv[]){
    // get the index to retrieve and the field data is over
    unsigned long i = (argc > 1) ? atol(argv[1]) : 0;
    long p = (argc > 2) ? atol(argv[2]) : 2;
    unsigned long n_ = (argc > 3) ? atol(argv[3]) : 1;

    // set up BGV context and keys (CLIENT)
    auto t1 = chrono::high_resolution_clock::now();
    FHEcontext context = initBGV(p);
    FHESecKey secretKey(context);
    const FHEPubKey & publicKey = secretKey;
    secretKey.GenSecKey(64);
    addSome1DMatrices(secretKey);
    auto t2 = chrono::high_resolution_clock::now();

    if(DEBUG) cout << "Generated Key Pair" << endl;
    if(TIMED){
        auto t = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
        cout << "Initialized BGV params in: " << t/1000.0 << "s" << endl;
    }

    t1 = chrono::high_resolution_clock::now();
    // generate the DB based on our parameters
    EncryptedArray ea(context);
    // n_ must be a power of 2
    unsigned long l = ea.size();
    vector<vector<long> > db;
    util::generateDB(db, n_, l, p);
    t2 = chrono::high_resolution_clock::now();

    if(DEBUG){
        util::printDB(db);
        cout << "DB size is " << db.size() * db[0].size() << " elements" << endl;
    }
    if(TIMED){
        auto t = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
        cout << "Generated DB in: " << t/1000.0 << "s" << endl;
    }

    t1 = chrono::high_resolution_clock::now();
    // create the client
    PIRClient client(i, l);

    // generate the encrypted query (CLIENT)
    vector<long> s = client.queryGen(i, n_, l);
    if(DEBUG){
        cout << "Rotatated Query is: ";
        util::printVector(s);
    }
    Ctxt ctxt = client.encryptQuery(s, ea, publicKey);

    // create the server
    PIRServer server(db);

    // generate the reply (SERVER)
    vector<Ctxt> reply = server.replyGen(ctxt, ea);

    // extract the bit from the reply (CLIENT)
    long replyBit = client.replyExtract(reply, ea, secretKey);
    t2 = chrono::high_resolution_clock::now();
    cout << "\nRetrieved element @" << i << ": " << replyBit << endl;

    // compare against actual bit
    long actualBit = db[i/l][i%l];
    cout << "Actual element @" << i << ": " << actualBit << endl;

    if(TIMED){
        auto t = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
        cout << "Ran BGV PIR request and reply in: " << t/1000.0 << "s" << endl;
    }
}
