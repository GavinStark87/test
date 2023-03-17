/*
Gavin Stark
gestark
pa7
*/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

// Helper Functions (Optional) ---------------------------------------------



// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N){
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->left, N);
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if(R == nil){
		return R;
	} else if (R->key == k){
		return R;
	} else if (R->key > k) {
		return search(R->left, k);
	} else {
		return search(R->right, k);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
	if(R->left != nil){
		postOrderDelete(R->left);
	}
	if(R->right != nil){
		postOrderDelete(R->right);
	}
	delete(R);
	R = nil;
	num_pairs--;
	
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
	while(R->left != nil){
		return findMin(R->left);
	}
	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	while(R->right != nil){
		return findMin(R->right);
	}
	return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	Node* R = N;
	if(R->right != nil){
		return findMin(N->right);
	}
	Node* y = R->parent;
	while(y != nil && R == y->right){
		R = y;
		y = y->parent;
	}
	return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	Node* R = N;
	if(R->left != nil){
		return findMax(N->left);
	}
	Node* y = R->parent;
	while(y != nil && R == y->left){
		R = y;
		y = y->parent;
	}
	return y;
}

// Transplant
// Replaces value
void Dictionary::Transplant(Node* N, Node* V){
	if(N->parent == nil){
		root = V;
	} else if (N == N->parent->left){
		N->parent->left = V;
	} else {
		N->parent->right = V;
	}
	if (V != nil){
		V->parent = N->parent;
	}
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if(R != nil){
		inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + "\n";
		inOrderString(s, R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		s += R->key + "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// Class Constructors & Destructors ----------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	Node* N = new Node("Null", -99);
	nil = N;
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	Node* N = new Node("Null", -99);
	nil = N;
	root = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
	if(D.hasCurrent()){
		current = search(root, D.currentKey());

	} else {
		current = nil;
	}
}
	

// Destructor
Dictionary::~Dictionary(){
	clear();
	delete(nil);
}



// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
	Node* c = root;
	if(search(c, k) != nil){
		return true;
	} else {
		return false;
	}

}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
	if(search(root, k) == nil){
		throw std::logic_error("Dictionary: getValue(): not found");
	}
	return search(root, k)->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
	if(current != nil){
		return true;
	} else {
		return false;
	}
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
	if(!hasCurrent()){
		throw std::logic_error("Dictionary: currentKey(): not found");
	}
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if(!hasCurrent()){
		throw std::logic_error("Dictionary: currentVal(): not found");
	}
	return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	if(root != nil){
		postOrderDelete(root);
	}
	root = nil;
	current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	Node* y = nil;
    Node* x = root;
    while (x != nil){
        y = x;
        if (k < x->key){
            x = x->left;
        }else if (k > x->key){ 
            x = x->right;
        }else{
            x->val = v;
            return;
        }
    }
    Node* N = new Node(k,v);
    N->parent = y;
    N->left = nil;
    N->right = nil;
    num_pairs++;
    if (y == nil){
        root = N;    // tree T was empty
    }else if (k < y->key){
        y->left = N;
    }else{
        y->right = N;
    }
}


// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
	if(search(root, k) == nil){
		throw std::logic_error("Dictionary: remove(): not found");
	}
	Node* N = search(root, k);
	if(current == N){
		current = nil;
	}
	if(N->left == nil){
		Transplant(N, N->right);
	} else if (N->right == nil){
		Transplant(N, N->left);
	} else {
		Node* y = findMin(N->right);
		if (y->parent != N){
			Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
	}
	num_pairs--;

}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	if(num_pairs > 0){
		current = root;
		while(current->left != nil){
			current = current->left;
		}
	}
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	if(num_pairs > 0){
		current = root;
		while(current->right != nil){
			current = current->right;
		}
	}
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
	if(current == NULL){
		throw std::length_error("Dictionary: cursor(): cursor undefined");
	}
	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
	if(current == NULL){
		throw std::length_error("Dictionary: cursor(): cursor undefined");
	}
	current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	
	std::string s = "";
	if(num_pairs == 0){
		return s;
	}
	inOrderString(s, root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	std::string s = "";
	preOrderString(s, root);
	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	if(num_pairs != D.num_pairs){
		return false;
	}
	std::string s = "";
	std::string f = "";
	inOrderString(s, root);
	D.inOrderString(f, D.root);
	if(s == f){
		return true;
	} else {
		return false;
	}
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	if (this != &D){
		Dictionary temp = D;
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(nil, temp.nil);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}