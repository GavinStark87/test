#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
	BigInteger R = BigInteger("-0000011423");
	BigInteger N = BigInteger("+142355");
	BigInteger C = BigInteger("142355");
	BigInteger F = BigInteger("-142355");
	BigInteger Z = BigInteger("109764010237");
	BigInteger Y = BigInteger("1000000000");
	BigInteger P = BigInteger("111122223333");
	BigInteger Pp = BigInteger("111122223333");
	BigInteger I = BigInteger("123");
	BigInteger Ii = BigInteger("456");
	cout << Y << endl;
	cout << Z << endl;
	cout << R << endl << N << endl;
	cout << C.sign() << " " << N.sign() << endl;
	cout << N.compare(C) << " " << N.compare(R) << " " << N.compare(F) << " " << N.compare(Z) << endl;
	List L;
	L.insertBefore(1);
	L.insertBefore(-90);
	L.insertBefore(9);
	L.insertBefore(73);
	L.insertBefore(0);
	L.insertBefore(-500);
	cout << L << endl;
	BigInteger K = N + F;
	cout << K << endl;
	cout << endl;
	cout << N + Z << endl;
	cout << P * Pp << endl;
	cout << I << endl;
	cout << I * Ii << endl;
	
	/*for(L.moveFront(); L.position() < L.length(); L.moveNext()){
		cout << L.peekNext()*bas
	}*/

	return(0);
}