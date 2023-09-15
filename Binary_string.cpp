//To open and read a fasta file 
// using getline 
// shifting and matching the string and getting the binary string
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

    for (int shift = 1; shift <= 6; shift++) {
        string shift_seq = seq.substr(shift) + string(shift, 'N');
        string binary_string = "";

        for (size_t i = 0; i < seq.size(); i++) {
            if (seq[i] == shift_seq[i])
                binary_string += '1';
            else
                binary_string += '0';

        }
 
        cout << "Shift" << shift << ":" << binary_string << endl;
       }
    

    return 0;
}
