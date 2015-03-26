#include "PIRServer.hpp"

#include <string>

#include <NTL/lzz_pXFactoring.h>

#define DEBUG true
#define FOLD  false // optimization not yet implemented

PIRServer::PIRServer(vector<vector<long> > db_){
    db = db_;
}

vector<Ctxt> PIRServer::replyGen(Ctxt query, EncryptedArray & ea){
    if(FOLD){
        unsigned long n_ = db.size();
        vector<Ctxt> cs, prods;

        // shift the ciphertexts
        for(unsigned long i = 0; i < n_; ++i){
            const Ctxt & tmp = query;
            cs.push_back(tmp);
            ea.rotate(query, -1);  
        }

        // unfold ciphertexts (TODO)

        // multiply each row by the corresponding ciphertext
        for(unsigned i = 0; i < n_; ++i){
            PlaintextArray row(ea);
            row.encode(db[i]);
            //cs[i].multiplyBy(row);    // TODO: can't multiply ctxt w/ ptxt
            prods.push_back(cs[i]);
        }

        // sum the products
        Ctxt sum = prods[0];
        for(unsigned long i = 1; i < prods.size(); ++i)
            sum += prods[i];

        return prods;
    }
    else{
        // turn the DB into derived of PlaintextMatrixBaseInterface

        // compute the query times our database
        vector<Ctxt> reply = matrixMul(query, ea);
        return reply;
    }
}

vector<Ctxt> PIRServer::matrixMul(Ctxt & query, EncryptedArray & ea){
    vector<Ctxt> dotProds;
    long rows = db.size();
    vector<Ctxt> queries;

    // annoying but have to do this to because multByConst changes Ctxt val
    for(long i = 0; i < rows; ++i)
        queries.push_back(query);

    // multiply each row by query string
    for(long i = 0; i < rows; ++i){
        Ctxt out = queries[i];

        // encode col as plaintext
        PlaintextArray plainRow(ea);
        plainRow.encode(db[i]);

        // transform into polynomial
        ZZX rowPoly;
        ea.encode(rowPoly, plainRow);

        out.multByConstant(rowPoly);
        dotProds.push_back(out);
    }

    return dotProds;
}