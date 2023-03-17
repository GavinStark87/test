//-----------------------------------------------------------------------------
// Shuffle.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){
	if(D.length() == 1){
		return;
	}
	List first_half;
	List second_half;
	D.moveFront();
	for(int i = 0; i < D.length(); i++){
		if(i < D.length()/2){
			first_half.insertBefore(D.moveNext());
		} else {
			second_half.insertBefore(D.moveNext());
		}
		
	}
	D.clear();
	first_half.moveFront();
	second_half.moveFront();
	while(first_half.position() < first_half.length() || second_half.position() < second_half.length()){
		if(second_half.position() < second_half.length()){
			D.insertBefore(second_half.peekNext());
			second_half.moveNext();
		}
		if(first_half.position() < first_half.length()){
			D.insertBefore(first_half.peekNext());
			first_half.moveNext();
		}
		
	}
}


int main(int argc, char **argv){
	if(argc < 2){
		throw std::length_error("Shuffle: called with too few arguements");
	} else if (argc > 2){
		throw std::length_error("Shuffle: called with too many arguements");
	}

	List L;
	List R;
	int num_shuffles;
	cout << "deck size       shuffle count" << endl << "------------------------------" << endl;
	int end = atoi(argv[1]);
	
	for(int i = 1; i <= end; i++){
		num_shuffles = 0;
		L.insertBefore(i);
		R.insertBefore(i);
		shuffle(R);
		num_shuffles += 1;
		while(!(R.equals(L))){
			shuffle(R);
			num_shuffles += 1;
		}
		cout << i << "			" << num_shuffles << endl;
	}

	return(0);
}