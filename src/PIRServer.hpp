#include <vector>

// HElib files
#include "FHE.h"
#include "EncryptedArray.h"

class PIRServer{
private:
    vector<vector<long> > db;

public:
    PIRServer(vector<vector<long> > db);
    vector<Ctxt> replyGen(Ctxt query, EncryptedArray & ea);
    vector<Ctxt> matrixMul(Ctxt & query, EncryptedArray & ea);
};