#include "FoldingTree.hpp"

FoldingTree::FoldingTree(unsigned long n){
    root = new Node;
    buildTree(root, n);
}

FoldingTree::~FoldingTree(){
    destroyTree(root);
}

void FoldingTree::buildTree(Node * node, unsigned long n){
    if(node == 0) node = new Node;
    node->slen = n;
    node->left = 0;
    node->right = 0;

    // base case
    if(n == 2) return;

    unsigned long n1 = (int)(log2(n) / 2.0);
    unsigned long n2 = log2(n) - n1;
    node->left = new Node;
    node->right = new Node;

    // recursive case
    buildTree(node->left, (unsigned long)pow(2, n1));
    buildTree(node->right, (unsigned long)pow(2, n2));
}

void FoldingTree::destroyTree(Node * node){
    if(node != 0){
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void FoldingTree::printTree(Node * node){
    if(node != 0){
        printTree(node->left);
        printTree(node->right);
        cout << node->slen << endl;
    }
}

vector<long> FoldingTree::fold(Node * node, vector<long> query){
    // base case
    if(node->left == 0 && node->right == 0) return query;

    unsigned long d1 = node->left->slen;
    unsigned long d2 = node->right->slen;

    // find the search bit
    unsigned long j = 0;
    for(unsigned long i = 0; i < query.size(); ++i){
        if(query[i] == 1){
            j = i;
            break;
        }
    }

    // compute new "folded" query strings
    unsigned long alpha = floor(j / d2);
    unsigned long beta = j % d2;
    vector<long> l;
    vector<long> r;

    for(unsigned long i = 0; i < d1; ++i){
        l.push_back(i == alpha ? 1 : 0);
    }

    for(unsigned long i = 0; i < d2; ++i){
        r.push_back(i == beta ? 1 : 0);
    }

    // recursive case
    vector<long> a = fold(node->left, l);
    vector<long> b = fold(node->right, r);

    // combine the vectors
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

vector<long> FoldingTree::unfold(Node * node, vector<long> query){
    // base case
    if(node->left == 0 && node->right == 0) return query;

    unsigned long d1 = node->left->slen;
    unsigned long d2 = node->right->slen;
    unsigned long gamma1 = 2 * (unsigned long)log2(d1);
    unsigned long gamma2 = 2 * (unsigned long)log2(d2);

    // split the query i.e. "unfold" it
    vector<long> sl;
    vector<long> sr;

    for(unsigned long i = 0; i < gamma1; ++i)
        sl.push_back(query[i]);
    for(unsigned long i = gamma1; i < gamma1+gamma2; ++i)
        sr.push_back(query[i]);

    // recursive case
    vector<long> l = unfold(node->left, sl);
    vector<long> r = unfold(node->right, sr);

    // combine the two strings
    vector<long> q;
    for(unsigned long i = 0; i < d1 * d2; ++i) q.push_back(0);

    for(unsigned long a = 0; a < d1; ++a){
        for(unsigned long b = 0; b < d2; ++b){
            unsigned long i = a * d2 + b;

            // some "casting" has to happen since we have chars but need to
            // operate on integers
            q[i] = l[a] * r[b];
        }
    }

    return q;
}

Ctxt FoldingTree::unfold(Node * node, Ctxt query){
    // base case
    if(node->left == 0 && node->right == 0) return query;

    unsigned long d1 = node->left->slen;
    unsigned long d2 = node->right->slen;
    unsigned long gamma1 = 2 * (unsigned long)log2(d1);
    unsigned long gamma2 = 2 * (unsigned long)log2(d2);

    // split the query i.e. "unfold" it
    Ctxt sl(query.getPubKey(), query.getPtxtSpace());
    Ctxt sr(query.getPubKey(), query.getPtxtSpace());

    /* TODO - Make Homomorphic
    for(unsigned long i = 0; i < gamma1; ++i)
        sl.push_back(query[i]);
    for(unsigned long i = gamma1; i < gamma1+gamma2; ++i)
        sr.push_back(query[i]);
    */

    // recursive case
    Ctxt l = unfold(node->left, sl);
    Ctxt r = unfold(node->right, sr);

    // combine the two strings
    string q;
    q.assign(d1 * d2, '0');

    /* TODO - Make Homomorphic
    for(unsigned long a = 0; a < d1; ++a){
        for(unsigned long b = 0; b < d2; ++b){
            unsigned long i = a * d2 + b;

            // some "casting" has to happen since we have chars but need to
            // operate on integers
            q[i] = (l[a] - '0') * (r[b] - '0') + '0';
        }
    }
    */

    return query; // TODO - Return q
}
