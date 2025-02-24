#include "WordCount.h"
#include <iostream>
#include <sstream>  

using namespace std;

void testWordCount() {
    WordCount wc;
    wc.addAllWords("apple banana Apple cherry! banana, apple.");

    ostringstream out1, out2;  
    wc.dumpWordsSortedByWord(out1);
    wc.dumpWordsSortedByOccurence(out2);

    cout << "Sorted by word:\n" << out1.str();
    cout << "Sorted by occurrence:\n" << out2.str();
}

int main() {
    testWordCount();
    return 0;
}
