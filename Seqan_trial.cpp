// opening fasta file with seqan lib
#include <iostream>
#include <seqan/seq_io.h>

using namespace std;

int main() {
     seqan::Dna5String sequence;
     seqan::SeqFileIn seqFileIn;
     
     if (!seqan::open(seqFileIn, "/home/ccmb/imperfect_repeats/human_ref/T2T_chr1.fa")) {
        cerr << "Not able to open the file" << endl;
        return 1;
     }
     
     
     if (seqan::readRecord(sequence, seqFileIn) !=0) {
        cerr << "not able to read the file" << endl;
        return 1;
    
     }

     seqan::close(seqFileIn);
     
     string seqstring = seqan::toCString(sequence);
     
     cout << "Sequence: " << seqstring << endl;

     return 0;
}
