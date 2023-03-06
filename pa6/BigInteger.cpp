#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;
const long base  = 1000000000;
const int  power = 9;

// Helper Functions ---------------------------------------------------------

// clearZero()
// removes leading zeroes from a list
void clearZero(List& L){
	while(L.length() != 0 && L.front() == 0){
			L.moveFront();
			L.eraseAfter();
	}
}

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
	for(L.moveFront(); L.position() < L.length(); L.setBefore(L.moveNext()*-1));
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
	clearZero(L);
	if(L.length() == 0){
		return 0;
	}
	long carry = 0;
	long res;
	L.moveBack();
	while (L.position() > 0)
	{
		
		L.setBefore(L.peekPrev() + carry);
		if(L.peekPrev() >= base){
			carry = ((long)L.peekPrev()/base);
			res = (((long)L.peekPrev()/base)*base);
			L.setBefore(L.peekPrev() - res);
		} else if (L.peekPrev() < 0) {
			if(L.peekPrev()%base != 0){
				carry = ((long)L.peekPrev()/base) - 1;
				res = (carry*base) * -1;
				L.setBefore(L.peekPrev() + res);
			} else {
				carry = ((long)L.peekPrev()/base);
				res = (carry*base) * -1;
				L.setBefore(L.peekPrev() + res);
			}
		} else {
			carry = 0;
		}
		L.movePrev();
		if(carry > 0 && L.position() == 0){
			L.insertBefore(carry);
			carry = 0;
		} else if (carry < 0 && L.position() == 0){
			L.insertBefore(carry);
			L.movePrev();
		}
	}
	
	if(L.front() < 0){
		negateList(L);
		normalizeList(L);
		return -1;
	}
	clearZero(L);
	
	return 1;
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
	for(L.moveFront(); L.position() < L.length(); L.setBefore(L.moveNext()*m));
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
	S.clear();
	S.moveFront();
	if(A.length() > B.length()){
		B.moveBack();
		for(A.moveBack(); A.position() > 0; A.movePrev()){
			if(B.position() > 0){
				S.insertAfter(A.peekPrev() + sgn*B.peekPrev());
				B.movePrev();
			} else {
				S.insertAfter(A.peekPrev());
			}
		}
	} else {
		A.moveBack();
		for(B.moveBack(); B.position() > 0; B.movePrev()){
			if(A.position() > 0){
				S.insertAfter(A.peekPrev() + sgn*B.peekPrev());
				A.movePrev();
			} else {
				S.insertAfter(B.peekPrev()*sgn);
			}
		}
	}
	
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	if(p == 0){
		return;
	}
	L.moveBack();
	for(int i = 0; i < p; i++){
		L.insertBefore(0);
	}
}

// Class Constructors & Destructors -------------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
	digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	if(s.size() == 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	for(int i = 0; i < (int)s.size(); i++){
		if(s[i] == '+' || s[i] == '-' || ((char)s[i] >= 48 && (char)s[i] <= 57)){
			continue;
		} else {
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}
	int cur = 0;
	if(s[cur] == '-'){
		signum = -1;
		cur++;
	} else if(s[cur] == '+'){
		signum = 1;
		cur++;
	} else {
		signum = 1;
	}
	for(s[cur]; s[cur] == '0'; cur++);

	int end = s.size();
	if((end - cur) <= power){
		digits.insertAfter(std::stol(s.substr(cur, end - cur)));
	} else {
		while(end >= cur){
			if((end - power) < cur){
				if((end - cur) > 0){
					digits.insertAfter(std::stol(s.substr(cur, end - cur)));
				}
				break;
			} else{
				digits.insertAfter(std::stol(s.substr(end - power, power)));
				end = end - power;
			}
		}
	}
	clearZero(digits);
	if(digits.length() == 0){
		signum = 0;
	}
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	signum = N.signum;
	digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const{
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	
	if(sign() == 0 && N.sign() == 0){
		return 0;
	} else if(sign() > N.sign()){
		return 1;
	} else if (sign() < N.sign()){
		return -1;
	} else if (digits.length() > N.digits.length()){
		return 1;
	} else if (digits.length() < N.digits.length()){
		return -1;
	}
	
	List D = digits;
	List C = N.digits;
	C.moveFront();
	D.moveFront();
	while(D.position() < D.length() && D.peekNext() == C.peekNext()){
		D.moveNext();
		C.moveNext();
	}
	if(sign() == -1){
		if(D.position() == D.length()){
			return 0;
		} else if (D.peekNext() < C.peekNext()){
			return 1;
		} else {
			return -1;
		}
	} else {
		if(D.position() == D.length()){
			return 0;
		} else if (D.peekNext() > C.peekNext()){
			return 1;
		} else {
			return -1;
		}
	}
	
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	signum = 0;
	digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
	if(signum == 1){
		signum = -1;
	} else if (signum == -1){
		signum = 1;
	}
}



// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	if(signum == 0){
		return "0";
	} else if (digits.length() == 0){
		return "0";
	}
	std::string s = "";
	if(signum == -1){
		s += '-';
	}
	digits.moveFront();
	while(digits.position() < digits.length()){
		if(std::to_string(digits.peekNext()).size() < power && digits.position() != 0){
			for(int i = 0; i < power - (int)std::to_string(digits.peekNext()).size(); i++){
				s += "0";
			}
			s += std::to_string(digits.moveNext());
		} else {
			s += std::to_string(digits.moveNext());
		}
	}
	return s;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger retList;
	if(N.sign() == 0){
		retList.signum = this->signum;
		retList.digits = this->digits;
	}
	if(this->signum == 0){
		retList.signum = N.signum;
		retList.digits = N.digits;
	}
	if(N.sign() == 1 && this->sign() == 1){
		sumList(retList.digits, this->digits, N.digits, 1);
		normalizeList(retList.digits);
		retList.signum = 1;
	} else if (N.sign() == -1 && this->sign() == 1){
		sumList(retList.digits, this->digits, N.digits, -1);
		retList.signum = normalizeList(retList.digits);
	} else if (N.sign() == -1 && this->sign() == -1){
		sumList(retList.digits, this->digits, N.digits, 1);
		normalizeList(retList.digits);
		retList.signum = -1;
	} else if (N.sign() == 1 && this->sign() == -1){
		sumList(retList.digits, N.digits, this->digits, -1);
		retList.signum = normalizeList(retList.digits);
	}
	
	if(retList.digits.length() == 0){
		retList.signum = 0;
	}
	return retList;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger retList;
	if(N.sign() == 0){
		retList.signum = this->signum;
		retList.digits = this->digits;
	}
	if(this->signum == 0){
		retList.signum = N.signum;
		retList.digits = N.digits;
	}
	if(N.sign() == 1 && this->sign() == 1){
		sumList(retList.digits, this->digits, N.digits, -1);
		retList.signum = normalizeList(retList.digits);
	} else if (N.sign() == -1 && this->sign() == 1){
		sumList(retList.digits, this->digits, N.digits, 1);
		normalizeList(retList.digits);
		retList.signum = 1;
	} else if (N.sign() == -1 && this->sign() == -1){
		sumList(retList.digits, this->digits, N.digits, -1);
		
		retList.signum = -1 * normalizeList(retList.digits);
	} else if (N.sign() == 1 && this->sign() == -1){
		sumList(retList.digits, this->digits, N.digits, 1);
		normalizeList(retList.digits);
		retList.signum = -1;
	}
	
	if(retList.digits.length() == 0){
		retList.signum = 0;
	}
	return retList;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger retList;
	BigInteger thisp = *this;
	List Np = N.digits;
	
	if(this->signum == 0 || N.signum == 0){
		retList.signum = 0;
		return retList;
	}
	
	/*if(thisp.length() < N.digits.length()){
		thisp.moveFront();
		
		for(int i = 0; i < thisp.length(); i++){
			Np = N.digits;
			scalarMultList(Np, thisp.peekNext());
			shiftList(Np, i);
			sumList(ret, ret, Np, 1);
			normalizeList(ret);
			thisp.moveNext();
		}
	} else {*/
	Np.moveBack();

	for(int i = 0; i < Np.length(); i++){
		thisp.digits = digits;
		scalarMultList(thisp.digits, Np.peekPrev());
		shiftList(thisp.digits, i);
		retList += thisp;
		normalizeList(retList.digits);
		Np.movePrev();
	}
	//}
	if (this->signum == -1 && N.signum == 1){
		retList.signum = -1;
	} else if (this->signum == 1 && N.signum == -1){
		retList.signum = -1;
	} else {
		retList.signum = 1;
	}
	return retList;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) == 0;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) == -1;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) == 0 || A.compare(B) == -1);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) == 1;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) == 0 || A.compare(B) == 1);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.mult(B);
	return A;
}