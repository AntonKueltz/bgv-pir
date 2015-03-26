#include <vector>

// HElib files
#include "FHE.h"
#include "EncryptedArray.h"

class PIRClient{
private:
	unsigned long alpha;
	unsigned long beta;
	
public:
	PIRClient(unsigned long i, unsigned long l);
	vector<long> queryGen(unsigned long i, unsigned long n, unsigned long l);
	Ctxt encryptQuery(vector<long> s, EncryptedArray & ea, const FHEPubKey & pubKey);
	long replyExtract(vector<Ctxt> ctxt, EncryptedArray & ea, FHESecKey & secKey);
};