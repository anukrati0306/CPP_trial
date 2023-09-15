//To open and read a fasta file 
// using getline 
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;

int main () {
    ifstream file("/home/ccmb/imperfect_repeats/human_ref/T2T_humanref/T2T_chr1.fa");

    if (!file.is_open()){
        cerr << "Could not open file" << endl;
        return 1;
    }

    string line;
    string seq = "";

    while (getline(file, line)) {
        //to skip the line with >
        if (line[0] == '>')
        continue;

        seq += line;
    }

    file.close();
    cout << seq ;

    return 0;
}
