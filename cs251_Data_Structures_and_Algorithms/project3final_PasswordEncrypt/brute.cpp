#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "key.hpp"
#include "brute.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
std::string alphabet("abcdefghijklmnopqrstuvwxyz012345");
std::string s;
bool verbose = false;


Brute::Brute(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
}

void Brute::decrypt(const std::string& encrypted){
	
	
	// your code here
	Key encryptKey = Key(encrypted);
	int maxOps = (int)pow(32,C);
	for(int i = 0; i < maxOps; i++){
		//printf("test #%d\n", i);
		int bi[N];
		for(int j = 0; j < N; j++){
			bi[j]= 0;
		}
		int k = N -1;
		int num = i;
		while(num > 0){
			if(num % 2 == 0)
				bi[k] = 0;
			else
				bi[k] = 1;
			k--;
			num = num / 2;
		}
		int x;
		char y;
		for(int j = 0; j < N; j = j + 5){
			x = 0;
			x = bi[j]*16 + bi[j+1]*8 + bi[j+2]*4 + bi[j+3]*2 + bi[j+4]*1;
			//printf("X: %d\n", x);
			if(x >= 32)
				x = 0;
			y = alphabet[x];
			s[j/5] = y;

		}
		//printf("Length of Pass: %d", blah);
		//printf("C: %d", C);
		//printf("Pass: %s\n", s.c_str());
		Key tempKey = Key(s);
		if(tempKey.subset_sum(T, verbose) == encryptKey){
			printf("%s\n", s.c_str());
		}
	}


}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Brute force cracking of Subset-sum password with " 
		<< B << " bits precision\n"
	    << "USAGE: " << me << " <encrypted> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <encrypted>:   encrypted password to crack\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	encrypted = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]){
	
	initialize(argc, argv);
	
	// your code here
	Brute b(table_filename);
	b.decrypt(encrypted);
	return 0;
}
