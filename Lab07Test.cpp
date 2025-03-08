#include "WordCount.h"
#include "tddFuncs.h" 
#include <iostream>
#include <sstream>

using namespace std;

void testWordCount() {
    WordCount wc;
    wc.addAllWords("apple banana Apple cherry! banana, apple.");

    ostringstream out1, out2;
    wc.dumpWordsSortedByWord(out1);
    wc.dumpWordsSortedByOccurence(out2);

    string expectedSortedByWord = "apple,3\nbanana,2\ncherry,1\n";
    string expectedSortedByOccurence = "apple,3\nbanana,2\ncherry,1\n";

    ASSERT_EQUALS(expectedSortedByWord, out1.str());
    ASSERT_EQUALS(expectedSortedByOccurence, out2.str());
}

int main() {
    testWordCount();
    cout << "All tests passed!" << endl;
    return 0;
}

