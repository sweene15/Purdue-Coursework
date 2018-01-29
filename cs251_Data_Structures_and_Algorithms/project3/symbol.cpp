#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "key.hpp"
#include "symbol.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
std::string alphabet("abcdefghijklmnopqrstuvwxyz012345");
bool verbose = false;

Symbol::Symbol(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();	
	// insert your code here
	std::unordered_map<std::string, int> keyMap;
}

void Symbol::decrypt(const std::string& encrypted){
	// insert your code here
	std::unordered_map<std::string, std::string> _map;
	Key encryptKey = Key(encrypted);
	int secondHalf = C/2;
	int firstHalf = C - secondHalf;
	int maxOps = (int)pow(32,C);
	int secondHalfOps = (int)pow(32, secondHalf);
	int firstHalfOps = (int)pow(32, firstHalf);
	char* s[secondHalfOps];
	char* str[firstHalfOps];
	for(int i = 0; i < secondHalfOps; i++){
		s[i] = new char[secondHalf];
		//printf("secondHalf equals: %d\n", secondHalf);
		//printf("firstHalf equals: %d\n", firstHalf);
		std::string index = std::to_string(i);
		//printf("test# %d\n", i);
		int bi[N];
		for(int j = 0; j < 5*secondHalf; j++){
			bi[j] = 0;
		}
		int k = 5*secondHalf - 1;
		int num = i;
		while(num > 0){
			if(num % 2 == 0)
				bi[k] = 0;
			else
				bi[k] = 1;
			k--;
			num = num/2;
		}
		int x;
		char y;
		for(int j = 0; j < 5*secondHalf; j= j+5){
			x = 0;
			x = bi[j]*16 + bi[j+1]*8 + bi[j+2]*4 + bi[j+3]*2+ bi[j+4]*1;
			if(x>=32)
				x = 0;
			y = alphabet[x];
			s[i][j/5] = y;
		//	printf("value: %s\n", s.c_str());
		}
		s[i][5*secondHalf/5] = '\0';
		//printf("%s\n", s.c_str());
		_map.insert({index, s[i]});
		//printf("%s\n", _map.at(index).c_str());
		//printf("inserted# %d you feg\n", i);
	}

	for(int i = 0; i < firstHalfOps; i++) {
		int bj[N];
		str[i] = new char[firstHalf];
		for(int j = 0; j < 5*firstHalf; j++){
			bj[j]=0;
		}
		int k = 5*firstHalf - 1;
		int num = i;
		while(num > 0){
			if(num % 2 == 0)
				bj[k] = 0;
			else
				bj[k] = 1;
			k--;
			num = num/2;
		}
		int x;
		char y;
		for(int j = 0; j < 5*firstHalf; j = j+5){
			x = 0;
			x = bj[j]*16 + bj[j+1]*8 + bj[j+2]*4 + bj[j+3]*2 + bj[j+4]*1;
			if(x>=32)
				x = 0;
			y = alphabet[x];
			str[i][j/5] = y;
			//printf("%s\n", s.c_str());
		}
		str[i][5*firstHalf] = '\0';
		for(int j = 0; j < secondHalfOps; j++){

		
			std::string indexA = std::to_string(j);
	//		printf("%s\n", indexA.c_str());
			char* temp = new char[C];
			std::string temp2 = _map.at(indexA);
			int k;
			//printf("%s\n", str[i]);
			//printf("%s\n", temp2.c_str());
			for(k = 0; k < firstHalf; k++){
				temp[k] = str[i][k];
				//printf("%c\n", temp[k]);
			}
			int l = 0;
			while( k < C){
				temp[k] = temp2[l];
				//printf("%d\n", k);
				l++;
				k++;
			}
			Key tempKey = Key(temp);
			if(tempKey.subset_sum(T, verbose) == encryptKey){
				printf("%s\n", temp);
			}
			//printf("%s\n", temp);
			//printf("%s\n", _map.at(indexA).c_str());
		
		}
	}
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Symbol table-based cracking of Subset-sum password"
		<< " with " << B << " bits precision\n"
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
	//printf("test\n");		
	// insert your code here
	Symbol b(table_filename);
	b.decrypt(encrypted);
	//printf("test2\n");
	return 0;
}
