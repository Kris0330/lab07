#include "WordCount.h"
#include "tddFuncs.h" 
#include <iostream>
#include <sstream>

using namespace std;

void testWordCount() {
    WordCount wc;

    ASSERT_EQUALS("isn't", wc.makeValidWord("isn't"));
    ASSERT_EQUALS("mother-in-law", wc.makeValidWord("mother-in-law"));
    ASSERT_EQUALS("apple", wc.makeValidWord("...apple***"));
    ASSERT_EQUALS("", wc.makeValidWord("-$%#"));

    wc.incrWordCount("foo");
    wc.incrWordCount("Foo"); 
    wc.incrWordCount("bar");
    wc.incrWordCount("BAR"); 
    wc.incrWordCount("foo-bar");

    ASSERT_EQUALS(2, wc.getWordCount("foo"));
    ASSERT_EQUALS(2, wc.getWordCount("bar"));
    ASSERT_EQUALS(1, wc.getWordCount("foo-bar"));
    ASSERT_EQUALS(5, wc.getTotalWords());
    ASSERT_EQUALS(3, wc.getNumUniqueWords());

    wc.decrWordCount("foo");
    ASSERT_EQUALS(1, wc.getWordCount("foo"));
    wc.decrWordCount("foo");
    ASSERT_EQUALS(0, wc.getWordCount("foo"));

    wc.addAllWords("apple banana Apple cherry! banana, apple.");
    ostringstream out1, out2;
    wc.dumpWordsSortedByWord(out1);
    wc.dumpWordsSortedByOccurence(out2);

    string expectedSortedByWord = "apple,3\nbanana,2\ncherry,1\n";
    string expectedSortedByOccurence = "apple,3\nbanana,2\ncherry,1\n";

    ASSERT_EQUALS(expectedSortedByWord, out1.str());
    ASSERT_EQUALS(expectedSortedByOccurence, out2.str());

    cout << "All tests passed!" << endl;
}

int main() {
    testWordCount();
    return 0;
}
