/*
Gavin Stark
gestark
pa7
*/
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
	Dictionary* D = new Dictionary();
	D->setValue("a", 1);
	D->setValue("b", 2);
	D->setValue("c", 3);
	Dictionary* F = D;
	cout << F->equals(*D) << endl;
	cout << F->to_string() << endl;
	cout << D->size() << endl;
	cout << D->contains("b") << endl;
	D->begin();
	cout << D->getValue("a") << endl;
	cout << D->hasCurrent() << endl;
	cout << D->currentKey() << endl;
	cout << D->currentVal() << endl;
	cout << D->to_string() << endl;
	D->clear();
	cout << D->to_string() << endl;
	cout << F->to_string() << endl;
	F->remove("c");
	cout << F->to_string() << endl;
	F->begin();
	cout << F->currentKey() << endl;
	F->end();
	cout << F->currentKey() << endl;
	F->prev();
	cout << F->currentKey() << endl;
	F->next();
	cout << F->currentKey() << endl;

}