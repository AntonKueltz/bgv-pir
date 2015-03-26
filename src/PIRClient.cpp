#include "PIRClient.hpp"

// src files
#include "FoldingTree.hpp"
#include "Util.hpp"

#define DEBUG false
#define FOLD  false // optimization not yet implemented

PIRClient::PIRClient(unsigned long i, unsigned long l){
    alpha = i / l;
    beta = i % l;
}

vector<long> PIRClient::queryGen(unsigned long i, unsigned long n, unsigned long l){
    if(DEBUG) cout << "\nQuery alpha: " << alpha << " beta: " << beta << endl;

    // generate query string
    string q;
    for(unsigned long j = 0; j < n; ++j){
        if(j == alpha) q.push_back('1');
        else q.push_back('0');
    }

    if(DEBUG){
        cout << "Unfolded Query is: ";
        cout << q << endl;
    }

    // TODO - All these strings should really be vector<long>s
    if(FOLD){
        // fold the query
        Node * root = new Node; 
        FoldingTree ft(n);
        string s = ft.fold(ft.root, q);

        if(DEBUG){
            cout << "Folded Query is: ";
            cout << s << endl;
        }

        // pad and shift s
        while(s.length() < l) s.push_back('0');
        return util::circShiftRight(s, beta);
    }
    else{
        // don't fold, convert to vector<long>
        vector<long> s;
        for(unsigned long j = 0; j < l; ++j)
            s.push_back(j == beta ? 1 : 0);
        return s;
    }
}

Ctxt PIRClient::encryptQuery(vector<long> s, EncryptedArray & ea, const FHEPubKey & pubKey){
    Ctxt ctxt(pubKey);
    PlaintextArray ptxt(ea);
    ptxt.encode(s);
    ea.encrypt(ctxt, pubKey, ptxt);
    return ctxt;
}


long PIRClient::replyExtract(vector<Ctxt> ctxt, EncryptedArray & ea, FHESecKey & secKey){
    PlaintextArray reply(ea);
    ea.decrypt(ctxt[alpha], secKey, reply);
    vector<long> vreply;
    reply.decode(vreply);
    return vreply[beta];
}