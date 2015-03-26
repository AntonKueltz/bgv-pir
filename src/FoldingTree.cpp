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
    
    // clang ceil() promotes an int up to the next int (IDIOTIC)
    // removed ceil() call as a result...
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

string FoldingTree::fold(Node * node, string query){
    // base case
    if(node->left == 0 && node->right == 0) return query;    
    
    unsigned long d1 = node->left->slen;
    unsigned long d2 = node->right->slen;

    // find the search bit
    unsigned long j = 0;
    for(unsigned long i = 0; i < query.length(); ++i){
        if(query[i] == '1'){
            j = i;
            break;
        }
    }

    // compute new "folded" query strings
    unsigned long alpha = floor(j / d2);
    unsigned long beta = j % d2;
    string l;    
    string r;

    for(unsigned long i = 0; i < d1; ++i){
        if(i == alpha) l.push_back('1');
        else l.push_back('0');
    }

    for(unsigned long i = 0; i < d2; ++i){
        if(i == beta) r.push_back('1');
        else r.push_back('0');    
    }

    // recursive case
    string a = fold(node->left, l);
    string b = fold(node->right, r);

    return a.append(b);
}

string FoldingTree::unfold(Node * node, string query){
    // base case
    if(node->left == 0 && node->right == 0) return query;

    unsigned long d1 = node->left->slen;
    unsigned long d2 = node->right->slen;
    unsigned long gamma1 = 2 * (unsigned long)log2(d1);
    unsigned long gamma2 = 2 * (unsigned long)log2(d2);

    // split the query i.e. "unfold" it
    string sl;
    string sr;

    for(unsigned long i = 0; i < gamma1; ++i) 
        sl.push_back(query[i]);
    for(unsigned long i = gamma1; i < gamma1+gamma2; ++i)
        sr.push_back(query[i]);

    // recursive case
    string l = unfold(node->left, sl);
    string r = unfold(node->right, sr);

    // combine the two strings
    string q;
    q.assign(d1 * d2, '0');

    for(unsigned long a = 0; a < d1; ++a){
        for(unsigned long b = 0; b < d2; ++b){
            unsigned long i = a * d2 + b;
            
            // some "casting" has to happen since we have chars but need to
            // operate on integers
            q[i] = (l[a] - '0') * (r[b] - '0') + '0'; 
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
