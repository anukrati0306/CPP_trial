#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace boost;

void process_sequence(string seq) {
    int nseq = seq.length();
    dynamic_bitset<> lbset(nseq,5), rbset(nseq,3), Nbset(nseq,0);

    for(int i=0; i<nseq; i++) {
        char nuc = seq[i];
        uint bidx = nseq-1-i;

        switch (nuc)
        {
        case 'A': case 'a': // 00
            lbset[bidx] = 0; rbset[bidx] = 0; break;
        case 'C': case 'c': // 01
            lbset[bidx] = 0; rbset[bidx] = 1; break;
        case 'G': case 'g': // 10
            lbset[bidx] = 1; rbset[bidx] = 0; break;
        case 'T': case 't': // 11
            lbset[bidx] = 1; rbset[bidx] = 1; break;
        default: // no match probably N or any other nuc
            Nbset[bidx] = 1; break;
        }
    }

    vector<dynamic_bitset<>> shiftxor_bsets;
    for (uint shift=2; shift<=7; shift++) {
        dynamic_bitset<> lshift_bset = lbset << shift;
        dynamic_bitset<> rshift_bset = rbset << shift;
        dynamic_bitset<> shiftxor_bset = (~(lshift_bset ^ lbset) & ~(rshift_bset ^ rbset));
        
        cout << shift << "\t" << shiftxor_bset << "\n";
        vector<int> positions;
        for (int i=nseq-1; i>=0; i--) {
            int sidx = (nseq-1) - i;
            if (shiftxor_bset[i] == 1) {
                positions.push_back(sidx);
            }
        }

        for (int x: positions) {
            cout << x << "\n";
        }
        
        
        
        shiftxor_bsets.push_back(shiftxor_bset);
    }
}

int increment_number(int &x) {
    x += 1;
    return x;
}

int main () {
    ifstream file("/home/ccmb/Downloads/test_seq.fasta");

    if (!file.is_open()){
        cerr << "Could not open file" << endl;
        return 1;
    }
    
    string line, seq_name, seq;

    while(getline(file, line)) {
        if (line[0] == '>') {
            if (seq_name != "") {
                process_sequence(seq);
                seq = "";
            }
            seq_name = line.substr(1, line.find(' '));
        }
        else {
            seq += line;
        }
    }
    process_sequence(seq);

    file.close();
    return 0;
}