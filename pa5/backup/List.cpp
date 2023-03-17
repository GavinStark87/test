//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
    frontDummy = new Node(-99);
    backDummy = new Node(-99);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
    // make this an empty List
    frontDummy = new Node(-99);
    backDummy = new Node(-99);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	afterCursor = backDummy;
	beforeCursor = frontDummy;
    num_elements = 0;
	pos_cursor = 0;

   	// load elements of L into this List
   	Node* N = L.frontDummy->next;
	for (int i = 0; i < L.num_elements; i++){
		insertAfter(N->data);
		moveNext();
		N = N->next;
	}
}

// Destructor
List::~List(){
	clear();
	delete frontDummy;
	delete backDummy;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return(num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if( num_elements == 0 ){
       throw std::length_error("List: front(): empty List");
    }
    return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if( num_elements == 0 ){
       throw std::length_error("List: back(): empty List");
    }
    return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	if( !(0 <= pos_cursor ) || !(pos_cursor <= num_elements)){
		throw std::length_error("List: position(): invalid cursor position");
	}
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if( pos_cursor >= num_elements ){
       throw std::range_error("List: peekNext(): cursor out of range");
    }
	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if( 0 >= pos_cursor ){
       throw std::range_error("List: peekPrev(): cursor out of range");
    }
	return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	//cout << "clear" << endl;
	if(num_elements == 0){
		return;
	}
	moveFront();
	while(num_elements > 0){
		eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	pos_cursor = num_elements;
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
	if( pos_cursor >= num_elements ){
       throw std::range_error("List: moveNext(): no next element");
    }
	pos_cursor++;
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if( 0 >= pos_cursor ){
       throw std::range_error("List: movePrev(): no previous element");
    }
	pos_cursor--;
	afterCursor = afterCursor->prev;
	beforeCursor = beforeCursor->prev;
	return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	beforeCursor->next = N;
	afterCursor->prev = N;
	N->next = afterCursor;
	N->prev = beforeCursor;
	afterCursor = N;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	beforeCursor->next = N;
	afterCursor->prev = N;
	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if( pos_cursor >= num_elements ){
       throw std::range_error("List: setAfter(): no next element");
    }
	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if( 0 >= pos_cursor ){
       throw std::range_error("List: setBefore(): no previous element");
    }
	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if( pos_cursor >= num_elements ){
       throw std::range_error("List: eraseAfter(): no next element");
    }
	Node* N = afterCursor;
	afterCursor->next->prev = beforeCursor;
	beforeCursor->next = afterCursor->next;
	afterCursor = afterCursor->next;
	num_elements--;
	delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if( 0 >= pos_cursor ){
       throw std::range_error("List: eraseBefore(): no previous element");
    }
	Node* N = beforeCursor;
	beforeCursor->prev->next = afterCursor;
	afterCursor->prev = beforeCursor->prev;
	beforeCursor = beforeCursor->prev;
	num_elements--;
	pos_cursor--;
	delete N;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
	//cout << "findNext" << endl;
	while(pos_cursor < num_elements){
		if(peekNext() == x){
			moveNext();
			return pos_cursor;
		}
		moveNext();
	}
	pos_cursor = num_elements;
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	//cout << "findPrev" << endl;
	while(pos_cursor > 0){
		peekPrev();
		if(peekPrev() == x){
			movePrev();
			return pos_cursor;
		}
		movePrev();
	}
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	//cout << "cleanup" << endl;
	Node* N = nullptr;
	ListElement info;
	int lC = 0;
	int index = 0;
	int list[num_elements];
	bool found = false;
	N = frontDummy->next;
	while(N != backDummy){
		found = false;
		info = N->data;
		for(int i = 0; i < lC; i++){
			if(list[i] == info){
				Node* M = N;
				if(index <= pos_cursor){
					pos_cursor--;
				}
				if(N == beforeCursor){
					beforeCursor = beforeCursor->prev;
				} else if (N == afterCursor){
					afterCursor = afterCursor->next;
				}
				N->prev->next = N->next;
				N->next->prev = N->prev;
				N = N->next;
				delete M;
				num_elements--;
				found = true;
				break;
			}
		}
		if(found != true){
			list[lC] = info;
			lC++;
			N = N->next;
			index++;
		}
	}
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
//	cout << "concat" << endl;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;
	List R;
	while(N != this->backDummy){
		R.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		R.insertBefore(M->data);
		M = M->next;
	}
	R.pos_cursor = 0;
	R.beforeCursor = R.frontDummy;
	R.afterCursor = R.frontDummy->next;
	return R;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	//cout << "to string" << endl;
	if(num_elements == 0){
		return "()";
	}
	Node* N = nullptr;
	std::string s = "(";

	for(N = frontDummy->next; N->next != backDummy; N = N->next){
		s += std::to_string(N->data) + ", ";
	}
	s += std::to_string(N->data) + ")";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	// << "equals" << endl;
	if(length() != R.length()){
		return false;
	}
	Node* N = frontDummy->next;
	Node* M = R.frontDummy->next;
	while(N != backDummy || M != R.backDummy){
		if(N == backDummy){
			return false;
		} else if (M == R.backDummy){
			return false;
		} else if (N->data != M->data){
			return false;
		}
		N = N->next;
		M = M->next;
	}
	return true;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if( this != &L){
		List temp = L;
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
	}

	return *this;
}

