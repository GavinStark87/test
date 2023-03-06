#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(int argc, char **argv){
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	std::string s;
	getline(in, s);
	BigInteger A = BigInteger(s);
	getline(in ,s);
	getline(in, s);
	BigInteger B = BigInteger(s);
	BigInteger two = BigInteger("2");
	BigInteger three = BigInteger("3");
	BigInteger nine = BigInteger("9");
	BigInteger sixteen = BigInteger("16");
	out << A << endl << endl;
	out << B << endl << endl;
	out << A + B << endl << endl;
	out << A - B << endl << endl;
	out << A - A << endl << endl;
	out << (three * A) - (two * B) << endl << endl;
	out << A*B << endl << endl;
	out << A * A << endl << endl;
	out << B * B << endl << endl;
	out << (nine * (A * A * A * A)) + (sixteen * (B * B * B * B * B)) << endl << endl;


	in.close();
	out.close();
	return(0);
}