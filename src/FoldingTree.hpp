#include <cmath>
#include <iostream>
#include <string>

#include "FHE.h"

using namespace std;

// a node in a binary tree
struct Node{
    unsigned long slen;	// length of the folded query at this node
    Node * left;		// left child in the tree
    Node * right;		// right child in the tree
};

// a structure that folds long queries into compressed ones
class FoldingTree{
public:
	// FIELDS
	Node * root;	// the root node of the tree


	// CONSTRUCTORS & DESTRUCTORS
	/* PARAMS:
	 * 		n - the length of the original query to be folded
	 * 
	 * Method delegates to buildTree
	 */
	FoldingTree(unsigned long n);

	/* Method delegates to destroyTree
	 */
	~FoldingTree();


	// METHODS
	/* PARAMS:
	 *		node - the node that will be the root of the tree
	 *		n - the length of the query string at this level 
	 *          (must be a power of 2)
	 *
	 * Method recursively builds a folding tree. Since n is a power of 2
	 * it can be written as 2^x. The value of n for the child nodes is then
	 * 2^(x/2) if x is even, and 2^(x/2 + 1), 2^(x/2) for left and right child
	 * respectively if x is odd. When x is 1 the current node will be a leaf. 
	 */
	void buildTree(Node * node, unsigned long n);

	/* PARAMS:
	 *		node - the node at which to start destroying the tree. If set to
	 *		       root the entire tree is destroyed, otherwise the subtree
	 *             rooted at node is destroyed.
	 *
	 *	Recursively traverses the tree, deleting nodes as they are visited.
	 */
	void destroyTree(Node * node);

	/* PARAMS:
	 *		node - the node at which to start printing the tree. If set to
	 *		       root the entire tree is printed, otherwise the subtree
	 *             rooted at node is printed.
	 *
	 *	Recursively traverses the tree, printing nodes as they are visited.
	 */
	void printTree(Node * node);

	/* PARAMS:
	 *		node - must be the root node for this procedure to work correctly.
	 *		query - a bit vector representing a query to retrieve index i. All
	 *		        bits are set to 0, except the ith bit which is set to 1.
	 *		        The length of query must be the same value as the slen field
	 *              of the root node.
	 *
	 * Recursive method that at each level represents the current query as a
	 * bit matrix. The left and right childs queries are the row and column
	 * (respectively) that contain the 1 bit in the matrix, represented as bit
	 * vectors.
	 * 
	 * RETURN:
	 * 		A string that is the concatentation of all the queries at the leaf
	 *		node level from leftmost leaf to rightmost leaf.
	 */
	string fold(Node * node, string query);

	/* PARAMS:
	 *		node - must be the root node for this procedure to work correctly.
	 *		query - a bit vector representing a query that has been compressed
	 *		        via the fold method.
	 *
	 * Unfolds a folded query back into it's original bit vector representation.
	 * 
	 * RETURN:
	 * 		a bit vector representing a query to retrieve index i. All bits are 
	 *		set to 0, except the ith bit which is set to 1.
	 */
	string unfold(Node * node, string query);

	/* PARAMS:
	 *		node - must be the root node for this procedure to work correctly.
	 *		query - a ciphertext representing a query that has been compressed
	 *		        via the fold method and encrypted via a FHE scheme.
	 *
	 * Unfolds a folded query back into it's original bit vector representation.
	 * 
	 * RETURN:
	 * 		an encrypted bit vector representing a query to retrieve index i.
	 */
	Ctxt unfold(Node * node, Ctxt query);
};